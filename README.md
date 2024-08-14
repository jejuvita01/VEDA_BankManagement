# VEDA_BankManagement

- VEDA에서 Qt를 활용한 미니 GUI 프로젝트 입니다. 
- 이 프로젝트는 CUI에서 구현한 프로젝트를 바탕으로 합니다. [링크](https://github.com/sm136599/VEDA_bank_management)

## 주요 화면 구성
- 화면은 총 6개로 구성됩니다.

### 메인 화면
- 메인 화면은 각 화면으로 넘어갈 수 있는 버튼이 있습니다.
- 로그인 버튼 - 로그인 화면
- 회원가입 버튼 - 회원가입 화면
- 상품 조회 버튼 - 상품 조회 화면
- 종료 버튼 - 전체 종료


### 로그인 화면
- id 와 pw를 데이터와 비교하여, 유저 화면과 매니저 화면으로 넘어갑니다.


### 회원가입 화면
- id 중복체크와 비밀번호 확인 하여, 데이터에 정보를 입력합니다.

### 상품 조회 화면
- 진행중인 상품을 보여줍니다.

### 유저 화면
- 자신의 전체 계좌를 둘러볼 수 있고, 입금, 출금, 해지까지 할 수 있습니다.
  - 단, 해지 시 안내문구가 안뜨므로 신중히 선택해 주세요.

### 매니저 화면
- 유저들의 계좌를 조회할 수 있습니다.
- 유저의 정보를 확인하고 유저를 삭제할 수 있습니다.
- 
