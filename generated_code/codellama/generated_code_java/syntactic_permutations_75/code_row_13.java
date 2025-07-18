public class Person {
    public int age;
    public String name;
}

public static Person[] allocateMemory(int count){
        return new Person[count];
}