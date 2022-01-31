txtfile = "AASDASDDAAAAAAAAERQREQREQRAAAAREWQRWERAAA"
STR = "AA"
for STR in txtfile:
        count = 0
        maxCount = 0
        for i in range(0, len(STR)):
            #count = 0
            while (txtfile[i : i+len(STR)] == STR):
                #print(txtfile[i : i+len(STR)])
                count += 1
                i += len(STR) - 1

            if count > maxCount:
                maxCount = count
            #count = 0
        
print(maxCount)
