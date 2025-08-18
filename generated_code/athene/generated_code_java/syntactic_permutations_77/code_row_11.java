import java.util.Arrays;

public class Person {
    int status;
    String name;

    public static void main(String[] args) {
        long sizeOfPerson = 16; // Assuming size of a person object (8 bytes for int, 8 bytes for reference to String)
        byte[] memoryBlock = new byte[(int)sizeOfPerson];
        
        Person john = new Person();
        john.status = 0;
        john.name = "John";
    }
}