from flask import Flask, request, jsonify
    from passlib.hash import sha256_crypt
    app = Flask(__name__)

    @app.route('/user', methods=['POST'])
    def add_user():
        username = request.json["username"]
        password = sha256_crypt.encrypt(request.json["password"])

        db.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, password))

        return jsonify({"message": "User added successfully!"})