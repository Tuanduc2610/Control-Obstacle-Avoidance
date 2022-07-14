            if distance<50:
                p1 = d[3]
                p2 = d[4]
                angle = calculate_angle(p1,p2)
                angle = round(angle*180/3.14,2)
                if 50<angle:
                    angle = 52
                elif 40<angle<=50:
                    angle = 45
                elif 30<angle<=40:
                    angle = 35
                elif 20<angle<=30:
                    angle = 25
                elif 10<angle<=20:
                    angle = 15
                elif angle<10:
                    angle = 0
                print(angle)
                a=1
                i2c.i2c(a, angle)