#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>

int main()
{
    unsigned int addr = inet_addr("1.2.3.4");
    unsigned int addr_err = inet_addr("Tomosom"); /* 返回0xffffffff,无意义 */
    struct in_addr addr1 = {0x09080706};
    struct in_addr addr2 = {0x05040302};
    /* inet_ntoa返回的字符串是同一片内存，因此使用strcpy做拷贝 */
    char *s1 = strcpy(malloc(32), inet_ntoa(addr1));
    char *s2 = strcpy(malloc(32), inet_ntoa(addr2));

    printf("addr = %x\n", addr);

    printf("addr1 = %x\n", addr1.s_addr);
    printf("addr2 = %x\n", addr2.s_addr);
    printf("s1 = %s\n", s1);
    printf("s2 = %s\n", s2);
    printf("s1 == s2 : %d\n", s1 == s2);

    /* 相比于inet_addr，inet_aton添加了错误判断 */
    if (inet_aton("Tomosom", &addr1)) {
        printf("addr1 = %x\n", addr1.s_addr);
    }

    free(s1);
    free(s2);

    /*
     * addr = 4030201
     * addr1 = 9080706
     * addr2 = 5040302
     * s1 = 6.7.8.9
     * s2 = 2.3.4.5
     * s1 == s2 : 0
     */

    return 0;
}