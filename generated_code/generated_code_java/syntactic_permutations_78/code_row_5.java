import java.util.ArrayList;

public class Person {
    private String name;
    private int age;
    private int status;

    public Person(String name, int age){
        this.name = name;
        this.age = age;
    }

    public void setStatus(int newStatus) {
        status = newStatus;
    }

    public int getStatus() {
        return status;
    }
}