from random import randint
from math import exp

import matplotlib.pyplot as plt


def currLength(citiesPath):
    
    global mapOFCities
    
    ans=0
    
    
    for i in range(1,len(citiesPath)):
        
        temPX= (mapOFCities[cities[i]][0]- mapOFCities[cities[i-1]][0])**2
        temPy= (mapOFCities[cities[i]][1]- mapOFCities[cities[i-1]][1])**2
        dist= (abs(temPX+temPy))**(0.5)
        
        ans+=dist
        
    temPX= (mapOFCities[cities[-1]][0]- mapOFCities[cities[0]][0])**2
    temPy= (mapOFCities[cities[-1]][1]- mapOFCities[cities[0]][1])**2
    dist= (abs(temPX+temPy))**(0.5)
        
    ans+=dist
    
    return ans
    
    
def suffle(citiesPath, l,  r):
    
    
    for i in range(l, r+1):
        
        
        temp=randint(l, r)
        
        citiesPath[i], citiesPath[temp]= citiesPath[temp], citiesPath[i]
    
    return citiesPath


def prFor(difference,temperature):
    
    return exp(-1*difference/temperature)

def randNumINRangeOFZeroToOne():
    
    t=1000000000000000000000000
    temp=randint(1, t)
    
    return temp/t
    
    


def iterate(temperature):
    
    global numOFCities, cr, absTemp, initialans, ans, cities, bestAns
    
    while(temperature > absTemp):

        r1=randint(0, numOFCities-1)
        r2=randint(0, numOFCities-1)

        l=min(r1, r2)
        r=max(r1, r2)
  
        cities=suffle(cities, l, r)
        
        newl=currLength(cities)
        
        ans = min(newl, ans)
            
        difference=newl-initialans
        
            
        if(difference <0 or (difference >0 and  prFor(difference,temperature) > randNumINRangeOFZeroToOne())):
            
            bestAns=[]
            for i in cities:
                bestAns.append(i)
            
            initialans=difference+initialans
        
        temperature=temperature*cr
    
    return cities




def plotTSP(bestAns, coords):

    

    x = []; y = []
    for i in bestAns:
        
        
        
        x.append(coords[i-1][0])
        y.append(coords[i-1][1])

    plt.plot(x, y, 'co')

    a_scale = float(max(x))/float(100)

    

    plt.arrow(x[-1], y[-1], (x[0] - x[-1]), (y[0] - y[-1]), head_width = a_scale,
            color ='g', length_includes_head=True)
    for i in range(0,len(x)-1):
        plt.arrow(x[i], y[i], (x[i+1] - x[i]), (y[i+1] - y[i]), head_width = a_scale,
                color = 'g', length_includes_head = True)


    plt.xlim(min(x)*1.1, max(x)*1.1)
    plt.ylim(min(y)*1.1, max(y)*1.1)
    plt.show()
    
    
    
global cities
cities = []

global mapOFCities
mapOFCities={}

coords=[]

# enter required data
dataSet="data/xqf131.txt"

with open(dataSet, "r") as file:
    for line in file.readlines():
        line = [float(x.replace("\n", "")) for x in line.split(" ")]
        # print(line)
        city= int(line[0])
        x= int(line[1])
        y= int(line[2])
            
        cities.append(city)
        coords.append([x, y])
            
        mapOFCities[city]= [x,y]
        
        


global numOFCities, cr, absTemp, initialans, ans, bestAns

numOFCities= len(mapOFCities)
bestAns=[]




cr=0.9
absTemp=0.00001
initialans=currLength(cities)

atmax=1000000000000000000000000

pr=1


bestAns= cities.copy()
ans= initialans
for _ in range(10):
    
    
    cities=iterate(atmax)
    
    cities=suffle(cities, 0, len(cities)-1)

    
print(bestAns)
print(ans)





plotTSP(bestAns, coords)
