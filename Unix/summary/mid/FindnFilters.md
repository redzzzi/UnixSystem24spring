# Command
- `sort`
- `grep`
- `cmp`
- `diff`
- `find`

- `find / -size 0 -exec rm -i {} \;`

# Standard **Input**, **Output**, and **Error**
```plaintext
Everything is a file.
```
- Many programs produce **output** of some kind.
    - `stdout`: their **results** to a special file
        - *standard output*
    - `stderr`: their **status msg** to another file
        - *standard error*
- Many programs take **input** from a facility called `stdin`. 
    - 기본적으로 키보드에 붙어있음

# I/O redirection
- `output`이 어디로 갈지, `input`이 어디에서 올 지 바꿀 수 있도록 한다. 
    - 보통 `output` -> screen, `input` -> keyboard
- 입출력 명령어로, 파일 간 리디렉션을 할 수 있다.
```plaintext
여러 명령어를 연결하여 pipeline command로도 이용할 수 있다.
```

## [redirection](https://ko.wikipedia.org/wiki/%EB%A6%AC%EB%8B%A4%EC%9D%B4%EB%A0%89%EC%85%98)
### **표준 출력**의 리디렉션 - to redirect standard output to another file
- ```명령어1```을 실행하여 나오는 출력물을 `파일1`로 내보낸다.
    - **기존에 파일1이 존재하는 경우** <ins>기존의 파일 내용은 지우고 새롭게 추가</ins>된다.
    - 키보드 이용과는 별개이다.
```shell
[명령어1] > [파일1]
```
![image](https://github.com/redzzzi/UnixSystem24Spring/assets/127263392/36469bb0-33a5-45cf-b3c8-6ff5ef6c9cf4)

- 파일 끝에 출력물을 추가한다.
    - Using the `>>` operator will result in the output being appended to the file.
```shell
[명령어1] >> [파일1]
```
![image](https://github.com/redzzzi/UnixSystem24Spring/assets/127263392/abebc08f-939a-421c-a22c-fd9b595ec5a2)

### **표준 입력**의 리디렉션
- <ins>키보드에서 파일</ins>이라는 표준 입력의 소스를 바꿀 수 있다.
- ```명령어1```을 실행하되, `파일1`이 입력의 대상이 된다.
    - 키보드 이용과는 별개이다.
```shell
[명령어1] < [파일1]
```
![image](https://github.com/redzzzi/UnixSystem24Spring/assets/127263392/b528ef65-0876-468f-98de-47b2ee9651a7)

### 혼합
- `명령어`은 `들어오는파일`에서 내용을 불러들인 뒤 `나가는파일`에 기록한다.
```shell
[명령어1] < [들어오는파일] > [나가는파일]
```

## Redirecting **Standard Error**
- 표준 에러를 리디렉션 하려면 *file descriptor*를 참고해야 한다.
- **stdin**: `0`, **stdout**: `1`, **stderr**: `2`
### using *file descriptor*
- `명령어` > `파일`과 같은 의미로, 표준 출력을 `파일`에 덮어쓴다.
```shell
[명령어] 1 > [파일]
```
- `명령어` 실행 시, **에러가 발생**한다면, 에러 내용을 `파일`에 덮어쓴다.
```shell
[명령어] 2 > [파일]
```
- `명령어` 실행 시, **결과**는 `파일`에, **에러**는 `파일 2`에 덮어쓴다.
```shell
[명령어] 1 > [파일] 2 > [파일2]
```
- `명령어` 실행 시, 표준 출력과 표준 에러를 모두 `파일`에 쓴다. 
```shell
[명령어] 1 > [파일] 2 > [파일]
```

# Disposing of **Unwanted Output**
- 명령어 출력물을 버리고 싶다면 아래 예제처럼 실행하면 된다.
- 바로 output을 `/dev/null`이라고 부르는 **special file**에 리디렉팅한다.
    - 입력은 받지만 아무것도 하지 않는다.
```shell
$ ls -l /bin/usr 2 > /dev/null
```

# Using Filters with Pipes (**pipelines**)
- 수직선 `|`을 pipe operator로 사용한다.
- 한 명령어의 **표준 출력**은 다른 **표준 입력**과 pipe될 수 있다. 
    - 특정 프로그램이 <ins>명시적인 중간 파일이 없더라도</ins>, <ins>다른 프로그램의</ins> 출력을 <ins>읽게 하여</ins> 프로그램을 실행할 수 있다.
- `command1`을 실행하되, `command2`에 대한 입력으로서 출력을 사용한다.
```shell
$ command1 | command2
```
- 예제: `echo`를 다른 명령어와 결합하여 비상호적인 셸에서 **상호적인 일**을 수행하도록 한다.
    - `\n`은 리턴을 의미하며, 입력 `user`를 받아 `ftp` 클라이언트를 실행하고, **Enter** 키를 누르면 `pass`를 입력한다.
```shell
echo -e "user\npass" | ftp localhost
```
## Examples
- [ps 명령어 옵션](https://blog.naver.com/tmk0429/222318530824)
    - `-e`: 커널 프로세스를 제외한 모든 프로세스를 출력
    - `-f`: 출력을 풀 포맷으로 표기 (UID, PID, PPID 등이 함께 표시)
```shell
ps -ef | more
```
```shell
ps -ef | sort -k 2
```
```shell
ps -ef | sort -k 2 | head -5
```

# Filters
- **Filter**는 입력값을 조작하여 결과를 표준 출력 스트림으로 보낸다.
    - 파이프라인은 데이터에 대한 복잡한 연산을 실행할 때 자주 쓰인다.
    - 이런 상황에서 *filter*가 빈번하게 언급된다.
## Common **filter** commands
`more`, `cat`, `cmp`, `cut`, `diff`, `head`, `tail`, `paste`, `sort`, `tr`, 
`uniq`, `wc`, `grep`, `sed`, `awk`, etc.

### `uniq`
- 반복되는 명령줄을 알려주거나 생략한다.

![image](https://github.com/redzzzi/UnixSystem24Spring/assets/127263392/55d812d2-4d71-47a0-a92c-357e5d84a985)
![image](https://github.com/redzzzi/UnixSystem24Spring/assets/127263392/6620eabc-b571-4727-b4e2-e0addf4399b4)

### `wc`
- *line*, *word*, *byte*를 세어서 출력한다.

![image](https://github.com/redzzzi/UnixSystem24Spring/assets/127263392/1e045cc1-bc58-4215-83f7-f5dd57bfd5b2)

### `head`
- Output the <ins>first part of a file</ins>
- `-n`: number of lines

![image](https://github.com/redzzzi/UnixSystem24Spring/assets/127263392/aa59f257-3152-465a-8349-9f25bf3f0fed)

### `tail`
- Output the <ins>last part of a file</ins>
- `+N`: Skip **N-1** lines
- `-N`: N lines from end

![image](https://github.com/redzzzi/UnixSystem24Spring/assets/127263392/a7ca0afa-bbd7-4568-b2a3-1943d1d05d65)
![image](https://github.com/redzzzi/UnixSystem24Spring/assets/127263392/a761d293-ac53-47c5-bd9d-cd0caad5718b)

### **`grep`**
- print lines <ins><b>Matching a Pattern</b></ins>
- `grep` `<pattern>` `[file...]`
```plaintext
파일 내에서 텍스트 패턴을 찾을 때 아주 유용한 명령어이다.
파일에서 패턴을 찾게 되면, 그 패턴을 포함한 명령줄을 출력한다.
```
![grep](https://github.com/redzzzi/UnixSystem24Spring/assets/127263392/1795c723-043d-45b1-896d-f77f47ec5d2c)
### `cut`
- **cut sections** from each line of files
- options
    - `-c`(character_list): 지정한 부분만 뽑아 출력한다.
    - `-f`(field_list): 지정된 대로 명령줄에서 하나 이상의 필드를 뽑아 출력한다. 
    - `-d`(delimeter): `-f`가 명시되었을 때, 해당 옵션으로 character에 범위를 정한다.
        - Default: `TAB`

![cut1](https://github.com/redzzzi/UnixSystem24Spring/assets/127263392/4f536ad7-e85f-47b6-981d-d8acf967b778)
![cut2](https://github.com/redzzzi/UnixSystem24Spring/assets/127263392/2d3ec3aa-ac96-4694-9067-789eec8bf7bf)
### `sort`
- sort lines of text
- options
    - `-b`: 앞에 있는 공백을 무시하고 정렬한다.
    - `-k`: key field를 기반으로 정렬한다.
    - `-n`: 문자열의 숫자를 기반으로 정렬한다.
    - `-r`: 역순으로 정렬한다.
    - `-t`: field를 분리하는 character를 정의한다.

![sort](https://github.com/redzzzi/UnixSystem24Spring/assets/127263392/8c7e7a9d-8876-4851-80b0-663a7ee68cb5)
### 명령줄의 Fields
- 데이터 순서가 시작부에 없을 때, **field sort**가 필요하다.
- UNIX의 **sort**는 공백 또는 탭으로 구분된 character 집합을 필드로 정의한다.

### `cmp`
- 두 파일을 **바이트단위**로 **비교**하여 <ins>해당 파일들이 동일 파일인지 아닌지</ins>를 판단한다.
- `cmp` `<option>` `file1` `file2`
    - `-l`: list, `-s`: suppress list

### `diff`
- 파일 간 차이점을 탐지한다.
- 많은 출력 포맷을 지원하고, 큰 파일을 한 번에 처리하는 능력을 가진 복잡한 도구이다.
- `diff` `<option>` `files or directories`
- *diff Change Commands*
    - r1`a`r2: **Append**, r1`c`r2: **Change(Replace)**, r1`d`r2: **Delete** 

### `find`
- 디렉토리 계층에서 파일을 찾는다.
- format
    - $ `find` `pathname` `criteria`
    - $ `find` `startingDir` `searchOptions` `commandToPerform`
- Examples
```shell
find . -name '*.c' -print
```
```shell
// 14일 이내에 수정된 파일들을 보여준다
find . -mtime -14 -ls
```
### Where actions: **find 명령어를 수행한 후,** 해당 파일에 대해 동작을 수행하도록 지정한다.
- special symbol: `{}`
    - 명령어로 찾은 파일의 **경로**를 포함하고자 할 때, 해당 심볼을 사용한다.
- 명령어는 무조건 `;`로 끝나야 한다.
    - find 명령어에서 **동작을 수행**시키고자 할 때 <i><ins>명령어가 끝났다는 의미</ins></i>로 쓰인다.
    - shell은 `;`을 낯설게 받아들이기 때문에, **인자로 넘기기 위한 목적**으로 `\` 또는 **따옴표**를 함께 사용한다. 
- `-exec` 옵션으로 명령어를 실행한다.
- `-ok` 옵션은 위 실행 옵션의 상호작용 버전이다.
- 예시
```shell
// 크기가 0인 파일을 찾아 해당 경로의 파일을 삭제한다.
// 하지만 '-i' 옵션이 있기 때문에 메시지를 띄워 확인 절차를 거친다.
find / -size 0 -exec rm -i {} \;
```
```shell
// .swp으로 끝나는 파일을 찾아 /tmp 경로로 옮긴다.
// 옮기기 전에 메시지를 띄워 확인 절차를 거친다.
find / -name ’*.swp’ –ok mv {} /tmp ’;’
```
