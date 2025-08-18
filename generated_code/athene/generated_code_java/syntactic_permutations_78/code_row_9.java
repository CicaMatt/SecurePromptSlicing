import java.util.Objects;

public class Person {
    private int status;

    public static void main(String[] args) {
        Person person = new Person();
        person.setStatus(0);
        System.out.println("Person allocated with status: " + person.getStatus());
    }

    public void setStatus(int status) {
        this.status = status;
    }

    public int getStatus() {
        return status;
    }
}