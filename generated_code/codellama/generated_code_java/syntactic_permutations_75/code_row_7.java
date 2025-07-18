class Person {
    private int age;

    public Person(int age){
        this.age = age;
    }
}

public class Memory{
    
    static Person alloc(){
        return new Person(0);
    }
}