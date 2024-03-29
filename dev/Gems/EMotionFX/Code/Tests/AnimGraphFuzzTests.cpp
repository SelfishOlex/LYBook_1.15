/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/

#include <iostream>
#include <vector>
#include <regex>
#include <AzCore/Math/Random.h>
#include <EMotionFX/Source/AnimGraph.h>
#include <EMotionFX/Source/AnimGraphStateMachine.h>
#include <AzCore/IO/ByteContainerStream.h>
#include <AzCore/Serialization/Utils.h>
#include "AnimGraphFixture.h"
#include <AzCore/Debug/TraceMessageBus.h>

namespace EMotionFX
{
    // Make it clear that the AnimGraphFuzzTest fixture is parameterized on a
    // seed value for a Random object
    using Seed = unsigned int;

    class AnimGraphFuzzTest
        : public AnimGraphFixture
        , public ::testing::WithParamInterface<Seed>
        , public AZ::Debug::TraceMessageBus::Handler
    {
        void SetUp()
        {
            AnimGraphFixture::SetUp();

            BusConnect();
        }

        void TearDown()
        {
            BusDisconnect();

            AnimGraphFixture::TearDown();
        }

        bool OnPreError(const char* window, const char* fileName, int line, const char* func, const char* message)
        {
            // These error messages will cause exceptions in debug builds.
            // Since the fuzz tests just make sure that the process doesn't
            // crash, we want to ignore these errors.
            static const std::vector<std::regex> ignoredErrorMessages
            {
                std::regex("^XML parse error: RapidXML Parse error"),
                std::regex("^ObjectStream XML parse error\\."),
                std::regex("^Unknown stream tag \\(first byte\\): '\\\\0' binary, '<' xml or '\\{' json!"),
                std::regex("^ObjectStream JSON load error: Stream is a newer version than object stream supports\\. ObjectStream version: .*"),
                std::regex("^Element .* in class .* is of type .* but needs to be type .*\\.")
            };

            return IsIgnored(ignoredErrorMessages, message);
        }

        bool OnPreWarning(const char* /*window*/, const char* /*fileName*/, int /*line*/, const char* /*func*/, const char* message)
        {
            // These warnings don't crash, but they make the test super chatty.
            // Just silence them.
            static const std::vector<std::regex> ignoredWarningMessages
            {
                std::regex("^Element .* of type .* is not registered as part of class .*\\. Data will be discarded"),
                std::regex("^Invalid UUID format .* \\(must be\\) \\{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx\\} \\(or without dashes and braces\\)")
            };

            return IsIgnored(ignoredWarningMessages, message);
        }

    private:
        bool IsIgnored(const std::vector<std::regex>& ignoredMessages, const char* message)
        {
            for (const std::regex& ignoredMessage : ignoredMessages)
            {
                if (std::regex_search(message, ignoredMessage))
                {
                    return true;
                }
            }

            return false;
        }
    };

    TEST_P(AnimGraphFuzzTest, TestLoad)
    {
        // Set the root state machine's Id so to ensure consistency between
        // test runs
        m_animGraph->GetRootStateMachine()->SetId(9347464774972852905u);
        AZStd::vector<char> charBuffer;
        AZ::IO::ByteContainerStream<AZStd::vector<char> > charStream(&charBuffer);
        AZ::Utils::SaveObjectToStream(charStream, AZ::ObjectStream::ST_XML, m_animGraph, GetSerializeContext());

        const Seed seed = GetParam();
        AZ::SimpleLcgRandom random(seed);

        const size_t bufSize = charBuffer.size();

        for (int i = 0; i < 10; ++i)
        {
            const unsigned int positionToEdit = random.GetRandom() % bufSize;
            const char newValue = random.GetRandom() % 256;
            charBuffer[positionToEdit] = newValue;

            EMotionFX::AnimGraph* animGraph = EMotionFX::AnimGraph::LoadFromBuffer(&charBuffer[0], bufSize, GetSerializeContext());
            if (animGraph)
            {
                delete animGraph;
            }
        }
    }

    static const std::vector<Seed> GetSeedsForTest(const int count)
    {
        AZ::SimpleLcgRandom random;
        std::vector<Seed> seeds(count);
        for (int i = 0; i < count; ++i)
        {
            seeds[i] = random.GetRandom();
        }
        return seeds;
    }

    const std::vector<Seed> randomSeeds = GetSeedsForTest(1000);

    INSTANTIATE_TEST_CASE_P(InstantiationName,
        AnimGraphFuzzTest,
        ::testing::ValuesIn(randomSeeds),
        ::testing::PrintToStringParamName()
    );

} //end namespace EMotionFX
