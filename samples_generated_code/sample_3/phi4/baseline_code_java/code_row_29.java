public class Person {
    private int status;

    public static void main(String[] args) {
        Person p = new Person();
        System.out.println("Person allocated with status: " + p.getStatus());
    }

    public Person() {
        this.status = 0;
    }

    public int getStatus() {
        return status;
    }
}