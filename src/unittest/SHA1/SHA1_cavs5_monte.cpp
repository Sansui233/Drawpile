/*******************************************************************************

   Copyright (C) 2007 M.K.A. <wyrmchild@users.sourceforge.net>

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
   DEALINGS IN THE SOFTWARE.

*******************************************************************************/

#include "shared/SHA1.h"

#include <iostream>
#include <memory>

// CAVS 5.0 / SHA-1 Monte
// 15 first digests
int main(int argc, char **argv)
{
	SHA1 hash;
	
	int c=-1;
	
	if (argc == 2)
		c = atoi(argv[1]);
	
	unsigned char res[][20] = {
		{0xda,0x39,0xa3,0xee,0x5e,0x6b,0x4b,0x0d,0x32,0x55,0xbf,0xef,0x95,0x60,0x18,0x90,0xaf,0xd8,0x07,0x09},
		{0xa1,0x62,0xb9,0x52,0xb5,0x99,0x96,0x4f,0x42,0xc0,0x69,0x6e,0xbb,0x93,0xf0,0x5d,0xa5,0x77,0x87,0x3b},
		{0x4f,0xe7,0x43,0x5f,0x44,0x81,0x86,0xf3,0x1b,0xaf,0x4f,0x7e,0x88,0x9c,0xb4,0x79,0xc9,0x51,0x28,0xfa},
		{0xa3,0x75,0x96,0xec,0x13,0xa0,0xd2,0xf9,0xe6,0xc0,0xb8,0xb9,0x6f,0x91,0x12,0x82,0x3a,0xa6,0xd9,0x61},
		{0x6c,0xf4,0x3c,0x60,0xf0,0xf0,0x2f,0xb0,0x82,0xe8,0xae,0x73,0xe4,0x59,0x50,0xb2,0x78,0x79,0x31,0xd6},
		{0x82,0xf3,0x5c,0x58,0x1c,0x10,0x71,0x7c,0x43,0x8b,0x34,0xcd,0x4d,0x43,0xe4,0xcc,0x46,0x2a,0xca,0xbf},
		{0xd9,0x68,0x7a,0xfa,0x44,0x84,0x8b,0x81,0x92,0xe2,0xac,0x64,0xd8,0xfb,0x6d,0xf6,0x71,0x39,0x72,0x5c},
		{0xbe,0x9b,0xf6,0xc6,0x06,0xee,0x6b,0x21,0x3f,0x01,0xd0,0x67,0x32,0xdb,0x3a,0xaa,0x2b,0x68,0xae,0x3d},
		{0x85,0xe5,0x32,0x71,0xe1,0x40,0x06,0xf0,0x26,0x59,0x21,0xd0,0x2d,0x4d,0x73,0x6c,0xdc,0x58,0x0b,0x0b},
		{0x7a,0xbb,0x9e,0x65,0xf9,0x20,0x50,0xbe,0x8b,0x2b,0xa5,0x76,0xb3,0x96,0x07,0xea,0xd8,0x76,0x74,0xb2},
		{0x6e,0x04,0xdf,0xa8,0x4b,0xbb,0xdf,0x31,0x60,0xfe,0x4e,0x6b,0xe6,0x69,0x4d,0x03,0x84,0x3a,0x89,0x06},
		{0x04,0x8a,0xb9,0xf2,0x2d,0x46,0x18,0xb7,0xe2,0x42,0x1b,0xc5,0x87,0x4d,0xfc,0x45,0x22,0x77,0xbb,0xbf},
		{0x22,0xc6,0x81,0x5a,0x9e,0x47,0x59,0x9f,0xdf,0x73,0x5c,0x97,0x30,0x0b,0xb7,0xf6,0xde,0x12,0xb9,0x8c},
		{0x7b,0xe1,0xe7,0xab,0xf2,0x8d,0x5a,0x8e,0x35,0x75,0xb1,0x73,0xcc,0xe4,0xcb,0x8f,0xc0,0xc0,0xd4,0xa5},
		{0x7b,0xd4,0xc0,0x66,0xb2,0x26,0x95,0x34,0xb7,0x0c,0xf0,0x3c,0x90,0xc6,0xfe,0x85,0x60,0xaa,0x74,0x5e},
		{0x98,0x3e,0x97,0x4c,0xfb,0xc0,0x27,0x6c,0x1c,0x3a,0x76,0x0f,0x8b,0xcc,0x54,0xc1,0xcd,0x35,0x1f,0x61},
	};
	
	if (c < 0 or c > int(sizeof(res)/20))
		return EXIT_FAILURE;
	
	unsigned char src[] = {0xbf,0x26,0x2d,0x96,0x4e,0xfc,0x61,0x17,0xba,0x31,0x9b,0x20,0xb5,0x3d,0xbd,0x1f,0xc7,0x17,0x3a,0xcc};
	
	for (int i=0; i != c; ++i)
		hash.Update(src, 20);
	hash.Final();
	
	unsigned char digest[20];
	hash.GetHash(digest);
	
	
	int rv = memcmp(digest, res[c], 20);
	if (rv != 0)
		std::cerr << "digest mismatch (count: "<<c<<")" << std::endl;
	
	return (rv == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}
