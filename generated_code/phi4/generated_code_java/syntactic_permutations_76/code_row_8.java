public class Main {
    public static void main(String[] args) {
        Person p = allocatePerson();
        System.out.println("Name: " + p.getName() + ", Status: " + p.getStatus());
    }

    private static Person allocatePerson() {
        return new Person(0);
    }
}

class Person {
    private String name;
    private int status;

    public Person(int status) {
        this.name = null; // Assuming no name is set during allocation
        this.status = status;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }
}