# project api demonstration(sample)

curl -X POST localhost:1026/account/signup -H "Content-Type: application/json" -d ''
# {"message":"body is required","status":"error"}

echo '\n'

curl -X POST localhost:1026/account/signup -H "Content-Type: application/json" -d '{"login": 7}'
# {"message":"missing login/email/password","status":"error"}

echo '\n'

curl -X POST localhost:1026/account/signup -H "Content-Type: application/json" -d '{"login":"jack", "email":"j123@yandex.ru", "password":"pass", "repeated password":"pass"}'
# {"creation_date":"2023-05-15 21:50:37.353158","email":"","message":"registeted ","status":"ok"}

echo '\n'

curl -X POST localhost:1026/account/signup -H "Content-Type: application/json" -d '{"login":"jack", "email":"j123@yandex.ru", "password":"pass", "repeated password":"another_pass"}'
# {"message":"wrong data","status":"error"}

echo '\n'

curl -X POST localhost:1026/account/login -H "Content-Type: application/json" -d '{"login":"jack", "password":"pass"}'
# {"message":"got verification","status":"ok","token":"amFjaw=="}

echo '\n'

curl -X DELETE localhost:1026/account/logout -H "Content-Type: application/json"
# {"message":"no token has been provided"}

echo '\n'

curl -X DELETE localhost:1026/account/logout -H "Content-Type: application/json" -H "Authorization: amFjaw=="

#{"message":"log out: successful for jack","status":"ok"}

echo '\n'

curl -X GET localhost:1026/account/settings -H "Content-Type: application/json" -H "Authorization: amFjaw=="
# {"birthday":"","clusters":"","creation_date":"","first_name":"","gender":"","last_name":"","login":"jack","status":"ok"}

echo '\n'

curl -X POST localhost:1026/account/settings -H "Content-Type: application/json" -H "Authorization: amFjaw=="
# {"message":"body is required","status":"error"}

echo '\n'

curl -X POST localhost:1026/account/settings -H "Content-Type: application/json" -H "Authorization: amFjaw==" -d '{"first_name":"new_Jack"}'
# {"message":"successfully defined account settings for jack","status":"ok"

echo '\n'

curl -X POST localhost:1026/account/settings -H "Content-Type: application/json" -d '{"first_name":"new_Jack"}'
# {"message":"no token has been provided"}

echo '\n'

curl -X PATCH localhost:1026/account/settings -H "Content-Type: application/json" -H "Authorization: amFjaw==" -d '{"first_name":"new_Jack"}'
# {"message":"settings fields have been edited","status":"ok"}

echo '\n'

curl -X GET localhost:1026/account/posts -H "Content-Type: application/json" -H "Authorization: aGVsbG8=" -d '{"posts":["value2","value3"]}'
# {"posts":[],"status":"ok"}

echo '\n'

curl -X POST localhost:1026/account/posts -H "Content-Type: application/json" -H "Authorization: aGVsbG8=" -d '{"posts":["value2","value3"]}'
# {"message":"posts have been set successfully","status":"ok"}

echo '\n'

curl -X DELETE localhost:1026/account/posts -H "Content-Type: application/json" -H "Authorization: aGVsbG8=" -d '{"posts":["value2","value3"]}'
# {"message":"posts have been deleted successfully","status":"ok"}

echo '\n'

curl -X GET localhost:1026/account/groups -H "Content-Type: application/json" -H "Authorization: aGVsbG8=" -d '{"posts":["value2","value3"]}'

# {"groups":[],"status":"ok"}

echo '\n'

curl -X DELETE localhost:1026/account/groups -H "Content-Type: application/json" -H "Authorization: aGVsbG8=" -d '{"posts":["value2","value3"]}'
# {"message":"groups have been deleted successfully","status":"ok"}

echo '\n'

curl -X POST localhost:1026/account/groups -H "Content-Type: application/json" -H "Authorization: aGVsbG8=" -d '{"posts":["value2","value3"]}'
# {"message":"groups have been set successfully","status":"ok"}

echo '\n'

curl -X GET localhost:1026/clusters -H "Content-Type: application/json"
# {"clusters":[],"status":"ok"}

echo '\n'

curl -X GET localhost:1026/clusters/groups -H "Content-Type: application/json"
# {"cluster_groups":[],"status":"ok"}