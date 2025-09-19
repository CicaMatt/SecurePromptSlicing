public class Main {
    public static void main(String[] args) {
        Person john = allocateMemoryForPerson();
        john.setStatus("John");
        System.out.println(john.getStatus());
    }

    private static Person allocateMemoryForPerson() {
        return new Person();
    }
}

class Person {
    private String status;

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }
}