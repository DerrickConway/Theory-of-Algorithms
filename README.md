# SHA 256 Secure Hash Algorithm

## What is a Secure Hash Algorithm

--------------------------------------------------------------------------------

A secure hash algorithm is actually a set of algorithms developed by the National Institutes of Standards and Technology (NIST)
and other government and private parties. These secure encryption or "file check" 
functions have arisen to meet some of the top cybersecurity challenges of the 21st century, 
as a number of public service groups work with federal government agencies to provide better 
online security standards for organizations and the public.

## SHA256 Algorithm in C

--------------------------------------------------------------------------------------------------------
You must write a program in the C programming language that calculates the SHA-256 hecksum of an input. 
The algorithm is speciﬁed in the Secure Hash Standard
document supplied by the (United States) National Institute of Standards and Technology. 
The only pre-requisite is that your program performs the lgorithm — you are free to decide what input the 
algorithm should be performed on.

Link, https://ws680.nist.gov/publication/get_pdf.cfm?pub_id=910977

### Need to install

--------------------------------------------------------------------------------
For this program I am using Google cloud to tun on virtual machine. You will need to sign up to google cloud.
You are going to need to install VI or VIM on your virtual machine this should be already installed on the virtual machine.
Next you need to install GIT and GCC:
First you need to update and install all the latest packages. The command you need to run is ```sudo apt-get update```, ```sudo apt-get upgrade```
Now you can install git.
```sudo apt-get install git build-essential```
After this you will have git and gcc installed.

### How this program works
When you run the program, you will run the following command

```
cd sha256
```
First you need to compile it.

```
gcc -o sha256 sha256.c
```
This is the command to run the program itself but also to specify the file that you wish to hash. 
In my example I will use the Sha256.c file itself as a test like so:
```
./sha256 test.txt
```


once you run this command you will be presented with a screen with the following:

```
**************************************************
SHA-256 convering from small endian to Big endian
**************************************************

-----------------------------Smail Endian------------------------------
eb922d95 e82b2b8b 5030e284 390352f3 3ac4986f 122a4eaa 929c2e02 f995dfce

------------------------Converted to Big endian------------------------

952d92eb 8b2b2be8 84e23050 f3520339 6f98c43a aa4e2a12 022e9c92 cedf95f9

**********************************************************************
```

### Resources

--------------------------------------------------------------------------------

<https://codereview.stackexchange.com/questions/151049/endianness-conversion-in-c> 

<https://www.geeksforgeeks.org/little-and-big-endian-mystery/>
