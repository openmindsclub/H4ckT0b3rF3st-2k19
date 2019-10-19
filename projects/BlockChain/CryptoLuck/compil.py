#!/usr/bin/python

"""
a small script to compile solidity scripts
into ABI,ByteCode and instructions to deploy
the smart contract using geth client
"""
from os import system
from sys import argv

sc = argv[1]

system("solc -o . --overwrite --bin --abi {}.sol".format(sc))
with open(sc+".abi","r") as f:
    abi = f.read()
with open(sc + ".bin","r") as f:
    bin = f.read()

o = "abi = {}\nbin = \"0x{}\"\n".format(abi,bin)+"c = eth.contract(abi)\npersonal.unlockAccount(eth.accounts[0])\nch = c.new({from: eth.accounts[0],data: bin,gas: 1000000,value: web3.toWei(1,\"ether\")})\nminer.start()\naddr = ch.address\n"

print o
#with open(sc,"w") as f:
#    f.write(o)

system("rm {}.abi {}.bin".format(sc,sc))