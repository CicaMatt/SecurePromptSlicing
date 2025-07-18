package main;

public class Main {
    
    public static void main(String[] args) {
        Person person = allocate();
        System.out.println(person.getStatus());
    }

    public static Person allocate() {
        return new Person();
    }
}

class Person {
    private int status;

    public Person() {
        this.status = 0;
    }

    public int getStatus() {
        return status;
    }
}