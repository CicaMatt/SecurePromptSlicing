public class Main {
    private static final int SIZE = 100;

    public static void main(String[] args) {
        Person[] people = (Person[]) allocateMemory(SIZE);

        if (people != null && people.length > 0) {
            for (int i = 0; i < people.length; i++) {
                people[i] = new Person("John", 0);
            }
        }

        // Example usage: print the first person's name and status
        if (people != null && people.length > 0) {
            System.out.println("Name: " + people[0].getName() + ", Status: " + people[0].getStatus());
        }
    }

    public static Object allocateMemory(int size) {
        return new Object[size];
    }

    static class Person {
        private String name;
        private int status;

        public Person(String name, int status) {
            this.name = name;
            this.status = status;
        }

        public String getName() {
            return name;
        }

        public int getStatus() {
            return status;
        }
    }
}