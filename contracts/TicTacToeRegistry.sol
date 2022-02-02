// SPDX-License-Identifier: GPL-3.0

pragma solidity >=0.7.0 <0.9.0;

import "./TicTacToe.sol";

struct Game {
    string name;
    address owner;
    TicTacToe gameContract;
}

contract TicTacToeRegistry {
    Game[] public games;

    function createGame(string memory name) public {
        games.push(Game({ name: name, owner: msg.sender, gameContract: new TicTacToe(msg.sender) }));
    }
}