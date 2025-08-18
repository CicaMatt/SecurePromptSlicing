import org.python.core.PyObject;
import org.python.util.PythonInterpreter;

public class WsgiApp {
    private static PyObject app;

    public static void main(String[] args) {
        PythonInterpreter interpreter = new PythonInterpreter();
        interpreter.exec("from flask import Flask\napp = Flask(__name__)\n@app.route('/')\ndef hello_world():\n    return 'Hello, World!'\n");
        app = (PyObject) interpreter.get("app");
        interpreter.exec("if __name__ == '__main__':\n    app.run()");
    }
}