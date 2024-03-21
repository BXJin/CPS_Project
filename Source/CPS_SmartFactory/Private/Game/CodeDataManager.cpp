// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/CodeDataManager.h"
#include "Game/CodeHttpActor.h"

// Sets default values
ACodeDataManager::ACodeDataManager() : StructIndex(0), StructDepth(0)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ACodeDataManager::BeginPlay()
{
	Super::BeginPlay();


	MainHttpActor = GetWorld()->SpawnActor<ACodeHttpActor>(ACodeHttpActor::StaticClass(), FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
	MainHttpActor->OnDataCompletedCallback.AddDynamic(this, &ACodeDataManager::GetMainData);

	MachineHttpActor = GetWorld()->SpawnActor<ACodeHttpActor>(ACodeHttpActor::StaticClass(), FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
	MachineHttpActor->OnDataCompletedCallback.AddDynamic(this, &ACodeDataManager::GetMachineData);

	FTimerHandle TimerHandle;
	if (IsValid(MainHttpActor))
	{
		SetCurDataTypeAndURL(EData::ED_Main);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACodeDataManager::SetTimerUpdateMainData, 2.0f, true);
	}

	if (IsValid(MachineHttpActor))
	{
		SetCurDataTypeAndURL(EData::ED_MachineData);
	}
}

// Called every frame
void ACodeDataManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACodeDataManager::SetCurDataTypeAndURL(EData CurDataType, const FString& Param1, const FString& Param2, const FString& Param3, const FString& Param4)
{
	FString AppendParam = "";
	if (Param1.IsEmpty() == false)
	{
		AppendParam.Append(Param1);
		if (Param2.IsEmpty() == false)
		{
			AppendParam.Append(FString::Printf(TEXT("/%s"), *Param2));
			if (Param3.IsEmpty() == false)
			{
				AppendParam.Append(FString::Printf(TEXT("/%s"), *Param3));
				if (Param4.IsEmpty() == false)
				{
					AppendParam.Append(FString::Printf(TEXT("/%s"), *Param4));
				}
			}
		}
	}

	switch (CurDataType)
	{
	case EData::ED_Main:
		DataURL = FString("http://3.34.116.91:8501/api/vcmdata/getmain");
		MainHttpActor->SetURL(DataURL, true);
		break;
	case EData::ED_MachineData:
		DataURL = FString("http://133.186.215.97:51000/hierarchy/");
		MachineHttpActor->SetURL(DataURL, false);
		break;
	default:
		break;
	}

}

void ACodeDataManager::GetMainData()
{
	auto MainData = MainHttpActor->ReturnObjectData();
	
	if (MainData != nullptr)
	{
		auto Datas = MainData->GetArrayField("data");
		if (Datas.IsEmpty())
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("empty"));
			return;
		}
		for (const auto& Value : Datas)
		{
			if (Value->Type == EJson::Object)
			{
				TSharedPtr<FJsonObject> ObjectPtr = Value->AsObject();
				auto type = ObjectPtr->GetIntegerField("type");
				if (type != 1)
				{
					// 필요한 필드들을 추출
					FString VcName = ObjectPtr->GetStringField("vcName");
					FString DataName = ObjectPtr->GetStringField("dataName");
					FString DataValue = ObjectPtr->GetStringField("dataValue");

					// TMap에 저장
					if (!StoredMainDataMap.Contains(VcName))
					{
						// "vcName"에 대한 TMap이 존재하지 않으면 새로 생성
						StoredMainDataMap.Add(VcName, FInnerMap());
					}

					// "vcName"에 대한 TMap에 데이터 추가                
					// "vcName"에 대한 TMap에서 데이터네임 검색
					FInnerMap& InMap = StoredMainDataMap[VcName];
					if (InMap.InnerMap.Contains(DataName))
					{
						InMap.InnerMap[DataName] = DataValue;
						//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("dff"));
					}
					else
					{
						InMap.InnerMap.Add(DataName, DataValue);
					}
				}
			}
		}

		if (OnMainDataValueCallBack.IsBound())
			OnMainDataValueCallBack.Broadcast();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("No!!!!Data"));
	}

}

void ACodeDataManager::SetTimerUpdateMainData()
{
	SetCurDataTypeAndURL(EData::ED_Main);
}

FString ACodeDataManager::ReturnMainDataValue(const FString& VcNameToAccess, const FString& DataNameToAccess)
{
	FString m_MainDataValue = "";
	if (StoredMainDataMap.Contains(VcNameToAccess))
	{
		const FInnerMap& m_InnerMap = StoredMainDataMap[VcNameToAccess];

		if (m_InnerMap.InnerMap.Contains(DataNameToAccess))
		{
			m_MainDataValue = m_InnerMap.InnerMap[DataNameToAccess];
		}
	}

	return m_MainDataValue;
}

void ACodeDataManager::GetMachineData()
{
	auto MachineData = MachineHttpActor->ReturnArrayData();
	
	if(MachineData.IsValidIndex(0))
		PushMachineDataStruct(MachineData);
}

void ACodeDataManager::PushMachineDataStruct(TArray<TSharedPtr<FJsonValue>> data)
{
	for (const auto& Value : data)
	{
		if (Value->Type == EJson::Object)
		{
			TSharedPtr<FJsonObject> ObjectPtr = Value->AsObject();
			FMachineDataStruct DataStruct;
			DataStruct.Index = StructIndex;
			DataStruct.Depth = StructDepth;
			DataStruct.NodeId = ObjectPtr->GetIntegerField("node_id");
			DataStruct.ParentId = ObjectPtr->GetIntegerField("parent_id");
			DataStruct.NodeName = ObjectPtr->GetStringField("node_name");
			DataStruct.Type = ObjectPtr->GetIntegerField("type");
			StructIndex++;

			const TArray<TSharedPtr<FJsonValue>>* ChildArray;
			if (ObjectPtr->TryGetArrayField("child", ChildArray))
			{
				DataStruct.HasChild = true;
				StoredMachineDataArray.Add(DataStruct);
				UE_LOG(LogTemp, Warning, TEXT("index ->> %d"), DataStruct.Index);
				StructDepth++;
				PushMachineDataStruct(*ChildArray);
				StructDepth--;
			}
			else
			{
				DataStruct.HasChild = false;
				StoredMachineDataArray.Add(DataStruct);
				UE_LOG(LogTemp, Warning, TEXT("index ->> %d"), DataStruct.Index);
			}
		}
	}
}
