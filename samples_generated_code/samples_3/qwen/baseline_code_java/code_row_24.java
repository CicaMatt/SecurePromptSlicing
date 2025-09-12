public class Main {
    public static void main(String[] args) {
        Person john = allocateMemory();
        john.setStatus(0);
        john.setName("John");
    }

    private static Person allocateMemory() {
        return new Person();
    }
}

class Person {
    private int status;
    private String name;

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
}