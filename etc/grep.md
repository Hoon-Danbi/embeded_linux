#######################
### grep

# 정규식 검색 
admin$ grep "lines.*empty" demo_file
Two lines above this line is empty.
admin$ 


# 검색 일치되는 횟수 
admin$ grep -c "line" demo_file
3
admin$ 

# 검색 일치된 텍스트만 출력 
admin$ grep -o "is.*line" demo_file
is line is the 1st lower case line
is line
is is the last line
admin$ 

# 검색 일치된 텍스트의 위치 출력 
admin$ grep -o -b "line" demo_file
51:line
line
170:line
line
206:line
admin$ 

# OR 을 이용한 검색 
admin$ grep 'Tech\|Sales' employee.txt
admin$ 
admin$ grep -E 'Tech|Sales' employee.txt 
100  Thomas  Manager    Sales       $5,000
200  Jason   Developer  Technology  $5,500
300  Raj     Sysadmin   Technology  $7,000
500  Randy   Manager    Sales       $6,000
admin$ egrep 'Tech|Sales' employee.txt 
admin$ 
admin$ grep -e Tech -e Sales employee.txt
admin$ 

# AND 을 이용한 검색 
admin$ grep -E 'Dev.*Tech' employee.txt
admin$ 
admin$ grep -E 'Manager.*Sales|Sales.*Manager' employee.txt
admin$ 
admin$ grep Manager employee.txt | grep Sales
admin$ 

# NOT 을 이용한 검색 
admin$ grep -v Sales employee.txt
200  Jason   Developer  Technology  $5,500
300  Raj     Sysadmin   Technology  $7,000
400  Nisha   Manager    Marketing   $9,500
admin$ egrep 'Manager|Developer' employee.txt | grep -v Sales
200  Jason   Developer  Technology  $5,500
400  Nisha   Manager    Marketing   $9,500

# 공백 라인의 갯수를 계산 
admin$ grep -c  "^$" myscript
3

# 라인의 시작과 끝을 검색 
admin$ grep "^root" /etc/passwd # check start
root:x:0:0:root:/root:/bin/bash
admin$ 
admin$ grep "terminated$" /var/log/syslog # check ending
Aug 31 07:35:14 linux anacron[9436]: Job `cron.daily' terminated

# `\+` 특수문자의 앞글자가 1회 이상 반복되는 경우를 검색
admin$ grep "hi \+hello" hi_hello.txt
hi hello
hi    hello how are you

# `*` 특수문자의 앞글자가 0회 이상 반복되는 경우를 검색
admin$ grep "hi *hello" hi_hello.txt
hi hello
hi    hello how are you
hihello

# `\?` 특수문자의 앞글자가 0 or 1회 되는 경우를 검색
admin$ grep "hi \?hello" input hi_hello.txt
hi hello
hihello

# grep

# 특수문자의 이스케이프 
admin$ grep "192\.168\.0\.2" /etc/network/interfaces
address 192.168.0.2
broadcast 192.168.0.255

# 정규식 
admin$ grep -B 1 "[0123456789]\+$" /etc/network/interfaces
admin$ 
admin$ grep -B 1 "[0-9]\+$" /etc/network/interfaces
admin$ 

지정한 글자로 시작하지 않는 문자열을 검색 
# a e i o u 로 시작하지 않는 문자열
admin$ grep -i  "^[^aeiou]" *

# IP만 반환하는 스크립트
admin$ /sbin/ifconfig eth0 | grep 'inet addr' | cut -d: -f2 | awk '{print $1}'

# IP 주소를 뽑아주는 스크립트
# 뽑아내야 할 IP 주소가 담겨있는 텍스트
admin$ ping -c 1 google.com
PING google.com (172.217.4.142): 56 data bytes
64 bytes from 172.217.4.142: icmp_seq=0 ttl=58 time=146.695 ms

--- google.com ping statistics ---
1 packets transmitted, 1 packets received, 0.0% packet loss
round-trip min/avg/max/stddev = 146.695/146.695/146.695/0.000 ms
admin$ 

# 결과
admin$ ping -c 1 google.com | grep -oE '[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3} \
\.[0-9]{1,3}'


#######################
### egrep 과 fgrep

# 스크립트 전달 인수를 체크( egrep.sh )
echo $1 | egrep '^[0-9]+$' # /dev/null
if [ $? -eq 0 ]; then
	numvar=$1
else
    echo "Invalid input"
    exit 1
fi

admin$ ./egrep.sh asd
Invalid input
admin$ ./egrep.sh 123
admin$ 

admin$ egrep -C 0 '(f|g)ile' *
admin$ egrep -C 0 '\(f\|g\)' *

# 정규식 검색 
admin$ fgrep -C 0 '(f|g)ile' *
admin$ fgrep -C 0 '\(f\|g\)ile' *