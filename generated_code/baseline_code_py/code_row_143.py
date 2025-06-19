from flask import request, jsonify
from sqlalchemy import create_engine, text

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    if email is None:
        return 'The email parameter is missing.', 400
    engine = create_engine('postgresql://user:password@localhost/database')
    with engine.connect() as conn:
        result = conn.execute(text("SELECT * FROM users WHERE email=:email"), {'email': email}).fetchone()
        if result is None:
            return 'You are not subscribed.', 400
        else:
            conn.execute(text("DELETE FROM users WHERE email=:email"), {'email': email})
            list_unsubscribe(email)
            return jsonify({'message': f'{email} has been deleted.'}), 201