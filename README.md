# Mc_MiniGames

This project only written by Korean.

---
팀명 '맥도날드'의 '미니게임천국' 입니다.
C와 C++를 이용하여 제작 중입니다.

---

### 프로그램 작성자들이 지켜주어야 할 규칙
#####1. 헤더파일 작성
-- 소스파일 생성 시, 같은 이름의 헤더파일 <*.h>를 생성한다.<br>
-- typedef, define, 함수원형은 헤더파일에 넣는다.<br>
#####2. 소스파일 저장 폴더
-- 처음부터 합쳐서 작업하면 100% 꼬일게 분명하므로, 각자의 폴더에서 따로 진행한다.<br>
-- \Games 에는 테스트가 다 끝난 소스파일만 넣을거임<br>
#####3. 네임스페이스 
-- 소스파일과 헤더파일의 (#include를 제외한) 모든 코드는 네임스페이스 내에 작성한다.<br>
 -- 네임스페이스의 이름은 <이니셜_게임명>으로 한다.<br>
 	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ex) SH_Dodge<br>
 -- ** 사용법 :: namespace <네임스페이스명> { // 모든 코드 } **
#####4. git push 후 알리기
-- 단톡방에 한 번씩만 언급해줍시다 <br>
-- 누군가가 push 했다고 하면 pull 한 번 해줍시다<br>

---
### 간단 Git Bash 사용법
#### 1. 지정 폴더 들어가기
-- ls :: 현재 디렉터리의 파일 및 하위 디렉터리를 보여준다<br>
-- cd <하위 디렉터리명> :: 하위 디렉터리로 이동한다<br>
-- cd.. :: 상위 디렉터리로 이동한다<br>

&nbsp;&nbsp;&nbsp;**1-1. git clone**<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-- github에 올라와 있는 파일을 (현재 디렉터리에) 다운 받는 명령어<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-- 최초 한 번만 하면 된다.<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;--**사용법 :: git clone https://github.com/ssoso27/Mc_MiniGames.git**<br>
&nbsp;&nbsp;&nbsp;**1-2. git pull**<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-- 현재 디렉터리의 프로젝트를 github에 올라온 최신 버전으로 업데이트 하는 명령어<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-- 항상 최신 버전을 유지하기 위해, 다른 팀원이 git pull을 했다면 git push를 해야한다.<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;--**사용법 :: git pull**<br>

#### 2. git add
-- 파일을 준비 영역에 추가하는 명령어<br>
-- **사용법 :: git add <파일 또는 폴더명>**<br>
####3. git commit
-- (git add로 추가된) 준비 영역의 파일을 최종 확정하는 명령어<br>
-- **사용법 :: git commit -m <파일 또는 폴더명> [파일에 대한 설명 문구]**<br>
####4. git push
-- (git commit으로 확정된) 파일을 원격 서버에 올리는 명령어<br>
-- 아마 처음엔 로그인 하라고 에러 메시지가 나올텐데, 침착하게 자기 아이디랑 비번을 입력하면 된다.<br>
-- **사용법 :: git push**<br>

####* 석 줄 요약
-- 한 번도 clone을 안 했을 경우, clone을 한다.<br>
-- **add -> commit -> push** 순으로 파일 업로드<br>
-- 다른 팀원들이 새로 업로드 했을 경우, pull을 한다.<br>
