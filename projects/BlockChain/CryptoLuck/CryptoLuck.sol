pragma solidity ^0.5.11;


contract CryptoLuck{
    uint8 luckyNumber;
    address admin;
    address[] addresses;
    address[] _tmp;
    
    struct user
    {
        string name;
        uint id;
        uint8 bet; 
    }
    
    mapping(address => user) users;
    

    modifier onlyAdmin()
    {
        require(msg.sender == admin);
        _;
    }
    
    modifier newVoter()
    {
        require(users[msg.sender].bet == 0);
        _;
    }

    constructor() public
    {
        admin = msg.sender;
    }

    function gamble(string memory _name,uint _id,uint8 _bet) public newVoter()
    {
        users[msg.sender] = user(_name,_id,_bet);
        addresses.push(msg.sender);
    }

    function setLuckyNumber() public onlyAdmin() returns(address)
    {
        uint _l = addresses.length;
        address winner;
        
        luckyNumber = uint8(uint( keccak256( abi.encodePacked( blockhash(block.number - 1) ) ) ) % 100) + 1;
        
        for(uint i=0;i<_l;i++)
        {
            if (users[addresses[i]].bet == luckyNumber) _tmp.push(addresses[i]);
        }
        if (_tmp.length != 0)  winner = _tmp[luckyNumber % _tmp.length];
        else winner = 0x0000000000000000000000000000000000000000;
        
        _tmp.length = 0;
            
        
        return winner;
        
    }

    function getTime() view public returns(uint)
    {
        return now;
    }
    
    function getLucky() public view returns (uint8)
    {
        return luckyNumber;
    }
}