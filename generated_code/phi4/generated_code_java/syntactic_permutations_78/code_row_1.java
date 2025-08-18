public class MemoryAllocator {
    private static final int STATUS_FREE = 0;
    private static final int STATUS_ALLOCATED = 1;

    public static class Person {
        private int status;

        public Person() {
            this.status = STATUS_FREE;
        }

        public int getStatus() {
            return status;
        }

        public void setStatus(int status) {
            this.status = status;
        }
    }

    public static Person allocatePerson(int size) {
        if (size <= 0) {
            throw new IllegalArgumentException("Size must be greater than zero.");
        }

        // Allocate memory for a person
        Person person = new Person();
        
        // Set the initial status of the person to STATUS_FREE
        person.setStatus(STATUS_FREE);

        return person;
    }

    public static void main(String[] args) {
        int size = 1; // Assuming size is the number of bytes you want to allocate

        // Allocate a new person and set the status to 0
        Person person = MemoryAllocator.allocatePerson(size);
        
        System.out.println("Person allocated with status: " + person.getStatus());
    }
}