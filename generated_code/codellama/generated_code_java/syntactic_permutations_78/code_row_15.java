private static Person allocate(int size) {
        return (Person) malloc(size);
    }

    private static void setStatus(int status) {
        this.status = status;
    }