public class Person {
    private int status;

    public static void main(String[] args) {
        Person p = new Person();
        System.out.println("Status: " + p.getStatus());
    }

    public int getStatus() {
        return status;
    }
}