local function makeConveyor(name, velocity)
    local conveyor = scene:getObjects(name)[1];
    conveyor.deadbodyAware = true;

    local rc = conveyor:findRenderStripeComponents("belt")[1];
    local ac = AnimationComponent(rc.drawable);
    ac:addAnimation(const.AnimationDefault, "belt1", 12.5 / velocity);
    ac:startAnimation(const.AnimationDefault);
    conveyor:addComponent(ac);

    conveyor:addComponent(CollisionSensorComponent());
    conveyor.objs = {};
    setSensorListener(name, function(other, args)
        if conveyor.objs[other.cookie] == nil then
            other.activeDeadbody = true;
            conveyor.objs[other.cookie] = { count = 1, obj = other };
        else
            conveyor.objs[other.cookie].count = conveyor.objs[other.cookie].count + 1;
        end
    end, function (other, args)
        if conveyor.objs[other.cookie] == nil then
            return;
        end
        conveyor.objs[other.cookie].count = conveyor.objs[other.cookie].count - 1;
        if conveyor.objs[other.cookie].count == 0 then
            local obj = conveyor.objs[other.cookie].obj;
            conveyor.objs[other.cookie] = nil;
            obj.activeDeadbody = false;
        end
    end);
    addTimeout0(function(cookie, dt)
        local dir = conveyor:getDirection(velocity * dt);
        for _, v in pairs(conveyor.objs) do
            v.obj:changePosSmoothed(dir.x, dir.y);
        end
    end);
end

local data = {
    [1] = {"e1m2", 8},
    [2] = {"e1m7", 8},
    [3] = {"e1m3", 7},
    [4] = {"e1m3", 15},
    [5] = {"e1m4", 6},
    [6] = {"e1m4", 12},
    [7] = {"e1m4", 18},
    [8] = {"e1m5", 19},
    [9] = {"e1m6", 4},
    [10] = {"e1m7", 17},
    [11] = {"e1m7", 10},
    [12] = {"e1m8", 3},
    [13] = {"e1m9", 2},
    [14] = {"e1m10", 4},
    [15] = {"e1m10", 1},
    [16] = {"e1m6", 15},
    [17] = {"e1m9", 5},
    [18] = {"e1m7", 10},
    [19] = {"e1m7", 22},
    [20] = {"e1m9", 8},
    [21] = {"e1m9", 7},
    [22] = {"e1m8", 12},
    [24] = {"e1m3", 6},
    [25] = {"e1m6", 0},
    [26] = {"e1m2", 19},
    [27] = {"e1m3", 1},
    [28] = {"e1m10", 3},
    [29] = {"e1m3", 18},
    [30] = {"e1m7", 0},
    [31] = {"e1m2", 10},
    [32] = {"e1m3", 1},
    [33] = {"e1m6", 15},
    [34] = {"e1m10", 1},
    [35] = {"e1m4", 0},
};

-- main

scene.player:findPlayerComponent():giveWeapon(const.WeaponTypeBlaster);
scene.player:findPlayerComponent():giveWeapon(const.WeaponTypeGG);

scene.camera:findCameraComponent():zoomTo(35, const.EaseLinear, 0);

scene.lighting.ambientLight = {0.5, 0.5, 0.5, 1.0};

scene.camera:findCameraComponent():setConstraint(scene:getObjects("constraint1")[1].pos, scene:getObjects("constraint2")[1].pos);

makeConveyor("conveyor0", 60.0);

for idx, idxData in pairs(data) do
    setSensorEnterListener(idx.."_cp", true, function(other)
        scene.cutscene = true;
        settings:setDeveloper(idxData[2]);
        stainedGlass({0, 0, 0, 0}, {0.0, 0.0, 0.0, 1.0}, const.EaseLinear, 0.25, function()
            stainedGlass({0, 0, 0, 1.0}, {0.0, 0.0, 0.0, 1.0}, const.EaseLinear, 100.0);
            scene:setNextLevel(idxData[1]..".lua", idxData[1]..".json");
        end);
    end);
end
