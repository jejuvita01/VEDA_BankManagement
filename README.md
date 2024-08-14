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

![image](https://github.com/user-attachments/assets/198a2b9e-90ab-4abc-a08b-31bec9a2e33e)


### 로그인 화면
- id 와 pw를 데이터와 비교하여, 유저 화면과 매니저 화면으로 넘어갑니다.

![image](https://github.com/user-attachments/assets/f7f27f0a-a670-497d-851c-83f33eb1fe2a)
![image](https://github.com/user-attachments/assets/f38cc15e-42a6-40db-ba55-4512dadb6d98)


### 회원가입 화면
- id 중복체크와 비밀번호 확인 하여, 데이터에 정보를 입력합니다.

![image](https://github.com/user-attachments/assets/25eebe5e-7325-48f4-8980-96e4fa33acd5)

- 아이디 중복 체크와 비밀번호 재확인이 완료되고 가입 완료를 클릭하면 가입이 완료됩니다.

![image](https://github.com/user-attachments/assets/ccb4a750-7d0d-4eaf-8888-9ed2281fe81d)


### 상품 조회 화면
- 진행중인 상품을 보여줍니다.

![image](https://github.com/user-attachments/assets/b58b3160-4ccd-4d4a-8ec6-d71ce4768343)


### 유저 화면
- 자신의 전체 계좌를 둘러볼 수 있고, 입금, 출금, 해지까지 할 수 있습니다.
  - 단, 해지 시 안내문구가 안뜨므로 신중히 선택해 주세요.
 
![image](https://github.com/user-attachments/assets/d61600cc-041c-467a-8c80-0cc3955376a5)

- 입출금, 해지는 우측 버튼을 통해할 수 있습니다.

![image](https://github.com/user-attachments/assets/695498be-78c9-4a96-9dc2-9d836fc301a3)

- 입금화면 (계좌 한도가 1억이므로 1억 - 잔액 만큼 입금할 수 있습니다.)

![image](https://github.com/user-attachments/assets/1c7bf153-7f10-4f60-84a8-00afaedc3c0c)

![image](https://github.com/user-attachments/assets/5588e33f-1301-4445-8e79-185213969bba)



![image](https://github.com/user-attachments/assets/a396ae5e-503b-4714-bab4-7b4e53e8b441)


### 매니저 화면
- 유저들의 계좌를 조회할 수 있습니다.
- 유저의 정보를 확인하고 유저를 삭제할 수 있습니다.

- 유저 전체 조회

![image](https://github.com/user-attachments/assets/99e34c96-b5c0-43bb-a861-96810be03561)

- 검색
  - 검색 시 해당 단어를 포함한 아이디 출력

![image](https://github.com/user-attachments/assets/5dedf6e4-fee1-419f-8751-47d3e20f0ac9)

- 삭제할 유저 조회

![image](https://github.com/user-attachments/assets/df5b0a1a-ba09-41e5-91b5-b00ddf58304c)

