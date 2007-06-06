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

#include <memory>

int main()
{
	SHA1 hash;
	
	unsigned char src1[] = "abc";
	
	hash.Update(src1, 3);
	hash.Final();
	
	char hexdigest[40];
	hash.HexDigest(hexdigest);
	
	char res1[] = "A9993E364706816ABA3E25717850C26C9CD0D89D";
	
	return (memcmp(hexdigest, res1, 40) == 0);
}