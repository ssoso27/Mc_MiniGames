# Mc_MiniGames

This project only written by Korean.

---
팀 '맥도날드'의 '미니게임천국' 입니다.
C와 C++를 이용하여 제작 중입니다.

---
### 진행 상황
#####메인화면 
-- 벽돌깨기, 화살표피하기, 슛골인, 같은 카드 찾기 연결 완료<br>
-- 테트리스 - 실행 시 에러 발생 <br>
-- 팀 소개 - 현재 작성되지 않음 <br>
#####강재희
--<br>
#####김수진
--<br>
#####양소희
-- 화살표 피하기<br>
-- 벽돌깨기<br>
-- 같은 카드 맞추기<br>
-- FlyBall (ing) <Br>
#####허승범
-- 테트리스 (수정 중) <br>
-- 공넣기<br>
-- 슈팅게임 (ing)<br>

---
### 프로그램 작성자들이 지켜주어야 할 규칙
#####1. 헤더파일 작성
-- 소스파일 생성 시, 같은 이름의 헤더파일 <*.h>를 생성한다.<br>
-- typedef, define, 함수원형은 헤더파일에 넣는다.<br>
#####2. 소스파일 저장 폴더
-- 처음부터 합쳐서 작업하면 100% 꼬일게 분명하므로, 각자의 폴더에서 따로 진행한다.<br>
-- \Games 에는 테스트가 다 끝난 소스파일만 넣을거임<br>
#####3. 주석 자주 달기
-- 주석을 달지 않는다면 일어날 일에 대해서는 굳이 언급하진 않겠습니다... <br>
-- 매우 끔찍해질 것이야 <br>
#####4. git push 후 알리기
-- 단톡방에 한 번씩만 언급해줍시다 <br>
-- 누군가가 push 했다고 하면 pull 한 번 해줍시다<br>
#####5.Issues 이용하기
-- 해결 못 한 버그나 구현하고 싶은 기능 등, 다른 팀원의 협력이 필요한 사항은 화면 상단의 Issues에 들어가서 올립시다.<br>

---
### 간단 Git Bash 사용법
#### 1. 지정 폴더 들어가기
-- ls :: 현재 디렉터리의 파일 및 하위 디렉터리를 보여준다<br>
-- cd <하위 디렉터리명> :: 하위 디렉터리로 이동한다<br>
-- cd .. :: 상위 디렉터리로 이동한다<br>

&nbsp;&nbsp;&nbsp;**1-1. git clone**<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-- github에 올라와 있는 파일을 (현재 디렉터리에) 다운 받는 명령어<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-- 최초 한 번만 하면 된다.<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;--**사용법 :: git clone https://github.com/ssoso27/Mc_MiniGames.git**<br>
&nbsp;&nbsp;&nbsp;**1-2. git pull**<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-- 현재 디렉터리의 프로젝트를 github에 올라온 최신 버전으로 업데이트 하는 명령어<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-- 항상 최신 버전을 유지하기 위해, 다른 팀원이 git push를 했다면 git pull를 해야한다.<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;--**사용법 :: git pull**<br>

#### 2. git add
-- 파일을 준비 영역에 추가하는 명령어<br>
-- **사용법 :: git add <파일 또는 폴더명>**<br>
-- ex) git add YSH/ <br>
-- ex) git add test.cpp <br>
####3. git commit
-- (git add로 추가된) 준비 영역의 파일을 최종 확정하는 명령어<br>
-- **사용법 :: git commit -m <파일 또는 폴더명> "파일에 대한 설명 문구"**<br>
-- ex) git commit -m YSH/ "커밋 테스트" <br>
####4. git push
-- (git commit으로 확정된) 파일을 원격 서버에 올리는 명령어<br>
-- 아마 처음엔 로그인 하라고 에러 메시지가 나올텐데, 침착하게 자기 아이디랑 비번을 입력하면 된다.<br>
-- **사용법 :: git push**<br>

####* 석 줄 요약
-- 한 번도 clone을 안 했을 경우, clone을 한다.<br>
-- **add -> commit -> push** 순으로 파일 업로드<br>
-- 다른 팀원들이 새로 업로드 했을 경우, pull을 한다.<br>

---

### 참고 사항
-- [C 게임 프로그래밍 강좌 블로그](http://nowcampus.tistory.com/entry/0%EC%9E%A5-C%EB%A5%BC-%EC%9D%B4%EC%9A%A9%ED%95%9C-%EA%B2%8C%EC%9E%84%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%98%EB%B0%8D-%EA%B0%95%EC%A2%8C%EB%A5%BC-%EC%8B%9C%EC%9E%91%ED%95%98%EA%B8%B0-%EC%A0%84%EC%97%90)

-- 프레임워크는 위 사이트의 Screen.h 를 따른다. (\미니게임천국\Games 에 파일 올려놨음)

-- 이건 내가 자주 쓰는 방법인데, git bash를 쓰는데 자꾸 (내가 해결 못 할) 에러가 뜨면, 내 작업파일을 다른 폴더에 백업해두고, 프로젝트 폴더를 삭제한 다음, 다시 clone 받아서 백업한 파일을 덮어씌우면 편하다 ... 사실 방금 내가 이상한 에러 떠서 쓰는거 맞음 
