local SimpleAI =
{
    Properties =
    {
        -- This is the target toward which you'll move
        MoveToEntity = {default=EntityId(), 
			description="Entity to move to."},
    }
}
 
function SimpleAI:OnActivate()
    -- Move!
    self.requestId = NavigationComponentRequestBus.
		Event.FindPathToEntity(
			self.entityId, 
			self.Properties.MoveToEntity)  
end
 
return SimpleAI