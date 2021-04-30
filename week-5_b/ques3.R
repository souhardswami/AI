library(bnlearn)
grades <- c("AA", "AB", "BB", "BC", "CC", "CD", "DD", "F")
course.grades<-read.table("2020_bn_nb_data.txt",head=TRUE)
course.grades.net<-hc(course.grades, score = "k2")
plot(course.grades.net)


course.grades.bn.fit <- bn.fit(course.grades.net, course.grades )
print(course.grades.bn.fit)



prob <- 0.00
ans = ""
for(value in grades) {
  p <- cpquery(course.grades.bn.fit, event = (PH100== value), evidence = (EC100=="DD" & IT101=="CC" & MA101=="CD"))
  if(p > prob) {
    ans <- value
    prob <- p
  }
}
print(ans)
