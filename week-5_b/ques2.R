library(bnlearn)
grades <- c("AA", "AB", "BB", "BC", "CC", "CD", "DD", "F")
course.grades<-read.table("2020_bn_nb_data.txt",head=TRUE)
course.grades.net<-hc(course.grades, score = "k2")
plot(course.grades.net)


course.grades.bn.fit <- bn.fit(course.grades.net, course.grades )
print(course.grades.bn.fit)
