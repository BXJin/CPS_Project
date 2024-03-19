개발 언어 : UE Blueprint, C++

서버 통신 관련 : UE - Http API 통신, CSV 및 Json 파싱, 파일 read

카메라 관련 : Pawn 마우스 이동/회전/줌, 타임라인

레벨 관련 : Persistent Level, 3D Widget Component(Actor)

Mesh 관련 : 하이라이트

UI 관련 : UUserWidget (c++), 위젯 바인딩, 팝업, UI 모듈화 (or Common UI)

패키징 : 커맨드 라인, config 파일을 사용한 프로젝트 세팅

기타 : 에러 발생 시 팝업, 데이터 불러오는 중 로딩, 해상도 조절



-좌측하단 버튼들 기획

[+]
최상위설비(ex. logheater) 메시가 없을 때 최상위 설비와 해당하는 자식설비들의 하이라이팅X, 카메라는 home 화면 카메라 transform으로 고정하기

[+]
병합이 필요하다고 판단되는 설비는 병합하기 (언리얼 에디터 상단 툴바 - 액터 > 병합)


[1]
1~8 : 하이라이팅 및 이동에 사용되는 설비 (해당 설비들만 사용)
0 : 레벨 라이팅 세팅
9 : 사용하지 않는 설비 모음


[2] 아웃라이너에서
ex) 5-1.TieRod(nodeId_26) : 폴더명, 상위 설비
RANCH_BOLT_1(nodeId_30)
RANCH_BOLT_2(nodeId_31)
RANCH_BOLT_3(nodeId_32)
RANCH_BOLT_4(nodeId_33)
ㄴ tie rod 버튼 클릭 시 RANCH_BOLT_1~4 설비(children) 전부 하이라이팅, RANCH_BOLT_1 버튼을 누르면 RANCH_BOLT_1 설비(+하위 설비) 하이라이팅


[3] 아웃라이너에서
2.hotsaw(nodeId_14)
GEAR_PUMP(nodeId_14)
와 같이 최상위 설비(hotsaw) 메시 이름에 적힌 node id와 중간 설비(GEAR_PUMP) 메시 이름에 적힌 node id가 동일할 때, (14 == 14)
중간 설비(GEAR_PUMP)메시와 최상위 설비(hotsaw) 메시의 하이라이팅 및 캠 동일하게 적용


[4] 아웃라이너에서
2.hotsaw(nodeId_14)
GEAR_PUMP(nodeId_14)
와 같이 중간 설비(GEAR_PUMP) 메시만 있고 최하위 설비(HYD_BLOCK) 메시가 없을 때,
최하위 설비(HYD_BLOCK) 버튼을 누르면 중간 설비(GEAR_PUMP) 설비와 동일하게 하이라이팅 및 캠 적용


[3]
[4] 예시
2.hotsaw(nodeId_14)
GEAR_PUMP(nodeId_14)
---------------------------------------------------------------------------------------------------------------
hotsaw 버튼을 누르면, GEAR_PUMP 메시 하이라이팅 및 GEAR_PUMP 메시로 캠 이동
GEAR_PUMP 버튼을 누르면, GEAR_PUMP 메시 하이라이팅 및 GEAR_PUMP 메시로 캠 이동
HYD_BLOCK 버튼을 누르면, GEAR_PUMP 메시 하이라이팅 및 GEAR_PUMP 메시로 캠 이동


[※]
http://133.186.215.97:51000/hierarchy/ api를 ui로 나타낼 때, type 0번만 나타내기 !!
(1 이상의 타입 설비가 아닌 데이터 타입이므로, ui(버튼)로 나타내지 않음)
