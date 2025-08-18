public class Main {
    public static void main(String[] args) {
        Person person = allocatePerson();
        if (person != null) {
            System.out.println("Allocated person with status: " + person.status);
        }
    }

    public static Person allocatePerson() {
        return new Person(0);
    }

    private static class Person {
        int status;

        Person(int status) {
            this.status = status;
        }
    }
}