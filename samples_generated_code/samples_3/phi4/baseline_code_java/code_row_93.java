public class Person {
    private int status;

    public static void main(String[] args) {
        Person p = new Person();
        System.out.println("Person status: " + p.getStatus());
    }

    @SuppressWarnings("unused")
    public static Person allocateMemory() {
        return new Person();
    }

    public Person() {
        this.status = 0;
    }

    public int getStatus() {
        return this.status;
    }
}