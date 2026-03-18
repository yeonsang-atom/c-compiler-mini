# C Compiler Implementation (Mini Compiler)

## 📌 Overview
이 프로젝트는 Lex와 Yacc 기반의 C 언어 컴파일러 부분 구현 프로젝트이다.  
어휘 분석, 구문 분석, 의미 분석, 코드 생성으로 이어지는 컴파일러의 전체 흐름을 이해하고 구현하는 것을 목표로 하였다.  

기본 Framwork가 제공된 상태에서, 주요 문법 규칙, AST 생성 로직, 의미 분석 일부를 직접 구현하였다.

---  

## 🏗️ Architecture

컴파일러는 다음과 같은 구조로 동작한다.

```
Source Code -> Lexer -> Parser -> AST -> Semantic Analysis -> Code Generation  
```

- **Lexer**: 토큰 생성 (`lex.l`)  
- **Parser**: 문법 기반 AST 생성 (`yacc.y`)  
- **Semantic Analysis**: 타입 및 식별자 검증 (`sem.c`)  
- **Code Generation**: 중간 코드 생성 (`codegen.c`)  

---  

## ⚙️ My Contributions  

- **Yacc를 이용한 문법 규칙 정의**
- **Lex를 이용한 토큰 패턴 구현**
- **AST 생성 로직 구현**
- **의미 분석 일부 구현**
  - 타입 검사
  - 식별자 검증
- 구문 분석 결과와 의미 분석 연결

---  

## 🔍 Parsing Strategy

컴파일러는 Yacc 기반 Bottom-up 파싱 방식을 사용하며,  
파싱 과정에서 AST를 생성하도록 문법 규칙을 설계하였다.  

---  

## 🧠 Core Data Structures

- **AST (추상 구문 트리)**  
  프로그램 구조를 트리 형태로 표현

- **심볼 테이블**  
  변수, 함수 등의 식별자 정보를 저장

- **타입 시스템**  
  타입 검사 및 의미적 오류 검증


---  

## 📈 What I Learned

- 컴파일러가 소스 코드를 처리하는 전체 흐름에 대한 이해
- 추상 구문 트리(AST)를 통해 프로그램 구조를 표현하는 방식
- Symbol Table을 통한 Scope 및 identifier 관리
- Syntax 분석과 Semantic 분석의 차이를 실제 구현을 통해 학습
- Yacc 기반 파싱과 의미 분석을 연결하는 과정 경험
- 컴파일러 설계 방식이 프로그램의 정확성에 미치는 영향을 학습
