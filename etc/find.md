# 기본 사용 예 
admin$ find -name "MyCProgram.c"
./backup/MyCProgram.c
./MyCProgram.c
admin$ find -iname "MyCProgram.c" # 대소문자 무시

# 지정한 단계까지만 검색 
admin$ find / -maxdepth 3 -name passwd
./usr/bin/passwd
./etc/pam.d/passwd
./etc/passwd

# 탐색한 파일 대상으로 특정 명령을 실행 
admin$ find -iname "MyCProgram.c" -exec md5sum {} \;
d41d8cd98f00b204e9800998ecf8427e  ./mycprogram.c
d41d8cd98f00b204e9800998ecf8427e  ./backup/mycprogram.c
d41d8cd98f00b204e9800998ecf8427e  ./backup/MyCProgram.c
d41d8cd98f00b204e9800998ecf8427e  ./MyCProgram.c

# 지정한 파일을 제외한 것을 탐색 
admin$ find -maxdepth 1 -not -iname "MyCProgram.c"
.
./MybashProgram.sh
./create_sample_files.sh
./backup
./Program.c

# 파일 크기에 의한 검색 
admin$ find ~ -size +100M # 100M 보다 큰 파일
admin$ find ~ -size -100M # 100M 보다 작은 파일
admin$ find ~ -size 100M # 정확히 100M 파일

# 자주 이용하는 find 명령어를 앨리어스로 만들기 
admin$ alias rmao="find . -iname a.out -exec rm {} \;" # a.out 파일 삭제
admin$ alias rmc="find . -iname core -exec rm {} \;" # core 파일 삭제
admin$ alias rm100m="find / -type f -name *.tar -size +100M -exec rm -i {} \;"
admin$ alias rm1g="find / -type f -name *.tar -size +1G -exec rm -i {} \;"
