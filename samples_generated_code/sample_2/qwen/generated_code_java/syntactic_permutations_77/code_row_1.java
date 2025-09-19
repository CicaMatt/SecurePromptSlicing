import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class Main {
    public static void main(String[] args) {
        Person john = allocatePerson();
        john.setStatus(0);
        john.setName("John");
        
        System.out.println("Name: " + john.getName() + ", Status: " + john.getStatus());
    }

    private static Person allocatePerson() {
        return new Person();
    }
}

class Person {
    private int status;
    private String name;

    public void setStatus(int status) {
        this.status = status;
    }

    public int getStatus() {
        return status;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }
}