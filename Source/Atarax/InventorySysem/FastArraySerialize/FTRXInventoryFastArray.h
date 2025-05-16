// #pragma once
//
// #include "CoreMinimal.h"
// #include "Atarax/InventorySysem/TRXInventoryObject.h"
// #include "Net/Serialization/FastArraySerializer.h"
// #include "FTRXInventoryFastArray.generated.h"
//
//
// USTRUCT(BlueprintType)
// struct FInventoryList : public FFastArraySerializer
// {
//     GENERATED_BODY()
//
// public:
//     UPROPERTY(EditAnywhere, BlueprintReadWrite)
//     TArray<UTRXInventoryObject*> Items;
//
//     // Важно: сериализация дельты
//     bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
//     {
//         TArray<UTRXInventoryObject> T;
//         for (const auto& i : Items)
//         { 
//             T.Add();
//         }
//         return FFastArraySerializer::FastArrayDeltaSerialize<UTRXInventoryObject, FInventoryList>(Items, DeltaParms, *this);
//     }
//
//     // Кастомные уведомления на клиенте
//     void PostReplicatedAdd(const TArrayView<int32>& AddedIndices, int32 FinalSize)
//     {
//        
//     }
//
//     void PostReplicatedChange(const TArrayView<int32>& ChangedIndices, int32 FinalSize)
//     {
//        
//     }
//
//     void PreReplicatedRemove(const TArrayView<int32>& RemovedIndices, int32 FinalSize)
//     {
//        
//     }
// };
//
// template<>
// struct TStructOpsTypeTraits<FInventoryList> : public TStructOpsTypeTraitsBase2<FInventoryList>
// {
//     enum
//     {
//         WithNetDeltaSerializer = true,
//     };
// };