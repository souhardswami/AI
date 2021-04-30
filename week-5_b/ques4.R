library(bnlearn)
library(caret)
grades <- c("AA", "AB", "BB", "BC", "CC", "CD", "DD", "F")
course.grades<-read.table("2020_bn_nb_data.txt",head=TRUE)

set.seed(100)
tIndex <- createDataPartition(course.grades$QP, p=0.7)$Resample1
train <- course.grades[tIndex, ]
test <- course.grades[-tIndex, ]

library(e1071)
nbc <- naiveBayes(QP~EC100+EC160+IT101+IT161+MA101+PH100+PH160+HS101, data = train)

printALL = function(model) {
  trainPred = predict(model, newdata = train, type = "class")
  trainTable = table(train$QP, trainPred)
  testPred = predict(nbc, newdata = test, type = "class")
  testTable = table(test$QP, testPred)
  trainAcc = (trainTable[1,1]+trainTable[2,2])/sum(trainTable)
  testAcc = (testTable[1,1]+testTable[2,2])/sum(testTable)
  print(round(cbind("Accuracy" =trainAcc, "Test " =testAcc), 6))
}

printALL(nbc)
