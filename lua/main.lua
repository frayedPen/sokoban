local WALL <const> = "#"
local BOX <const> = "O"
local SPOT <const> = "+"
local ON_SPOT <const> = "0"
local SPACE <const> = " "
local PLAYER <const> = "P"

local LAYOUT <const> = {
    {' ', ' ', '#', '#', '#', '#', '#', ' ', },
    {'#', '#', '#', ' ', ' ', ' ', '#', ' ', },
    {'#', '+', ' ', 'O', ' ', ' ', '#', ' ', },
    {'#', '#', '#', ' ', 'O', '+', '#', ' ', },
    {'#', '+', '#', '#', 'O', ' ', '#', ' ', },
    {'#', ' ', '#', ' ', '+', ' ', '#', '#', },
    {'#', 'O', ' ', '0', 'O', 'O', '+', '#', },
    {'#', ' ', ' ', ' ', '+', ' ', ' ', '#', },
    {'#', '#', '#', '#', '#', '#', '#', '#', },
}

local Vector2_meta = {
    __add = function (a, b)
        return Vector2(a.x + b.x, a.y + b.y)
    end
}

function Vector2(x, y)
    local self = setmetatable({}, Vector2_meta)

    self.x = x
    self.y = y

    return self
end

local function copyTable(tab)
    local tabCopy = {}

    for i, line in pairs(tab) do
        tabCopy[i] = {}

        for j, cell in pairs(line) do
            tabCopy[i][j] = cell
        end
    end

    return tabCopy
end

local function checkWin(level)
    if(level[3][2] == ON_SPOT and
        level[4][6] == ON_SPOT and
        level[5][2] == ON_SPOT and
        level[6][5] == ON_SPOT and
        level[7][4] == ON_SPOT and
        level[7][7] == ON_SPOT and
        level[8][5] == ON_SPOT) then
            return true
    end

    return false
end

local function render(level, player)
    for i, line in pairs(level) do
        for j, cell in pairs(line) do
            if i == player.y and j == player.x then
                io.write(PLAYER)
            else
                io.write(cell)
            end
        end

        io.write("\n")
    end

    if checkWin(level) then
        io.write("You won! Type restart to restart.\n");
    end

    io.write("\n")
end

local function getBlock(level, pos)
    if pos.x < 1 or pos.y < 1 or pos.y > 9 or pos.x > 8 then
        return nil
    end

    return level[pos.y][pos.x]
end

local function movePlayer(level, player, delta)
    local pos = player + delta

    local block = getBlock(level, pos)

    -- Check if player can move
    if block == WALL or block == nil then
        return
    end

    -- Check if player is trying to push a box
    if block == BOX or block == ON_SPOT then
        local nextPos = pos + delta
        local nextBlock = getBlock(level, nextPos)

        if nextBlock == SPACE or nextBlock == SPOT then
            -- Push block over
            level[pos.y][pos.x] = block == BOX and SPACE or SPOT
            level[nextPos.y][nextPos.x] = nextBlock == SPACE and BOX or ON_SPOT
        else
            return
        end
    end

    -- Move player
    player.x = pos.x
    player.y = pos.y
end

local switch = {
    ["w"] = function ()
        return Vector2(0, -1)
    end,

    ["a"] = function ()
        return Vector2(-1, 0)
    end,

    ["s"] = function ()
        return Vector2(0, 1)
    end,

    ["d"] = function ()
        return Vector2(1, 0)
    end
}

local function start()
    local player = Vector2(3, 3)
    local level = copyTable(LAYOUT)

    io.write("Type w,a,s,d to move. Can type multiple characters to move. Write reset to restart.\n")

    while true do

        render(level, player)

        io.write("Action: ")
        local inputStr = io.read()

        if inputStr == "exit" or inputStr == "leave" then
            return
        end

        if inputStr == "restart" or inputStr == "reset" then
            player = Vector2(3, 3)
            level = copyTable(LAYOUT)
        else
            -- Loop over each characters of the inputStr
            for i = 1, #inputStr do
                local c = inputStr:sub(i, i)
                
                local deltaFn = switch[c]
                
                if deltaFn ~= nil then
                    movePlayer(level, player, deltaFn())
                end

            end -- for

        end -- if restart

    end -- while

end

start()