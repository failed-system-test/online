t = input()
for i in range(int(input())):
    s = input()
    if(len(t) == len(s)):
        print("jntm!" if s == t else "friend!")
    elif (len(t) > len(s)):
        print("my child!" if s in t else "oh, child!")
    else:
        print("my teacher!" if t in s else "senior!")
