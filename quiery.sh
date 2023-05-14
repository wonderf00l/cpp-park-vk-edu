# project api demonstration(sample)

curl -X POST localhost:1026/account/signup -H "Content-Type: application/json" -d '{"login": 7}'

echo '\n'

curl -X POST localhost:1026/account/signup -H "Content-Type: application/json" -d '{"login":"jack", "email":"j123@yandex.ru", "password":"pass", "repeated password":"pass"}'

echo '\n'

curl -X POST localhost:1026/account/signup -H "Content-Type: application/json" -d ''

echo '\n'

curl -X POST localhost:1026/account/login?userId=55&passwd="hello"

echo '\n'

curl -X POST localhost:1026/account/exy/settings/?token=123

echo '\n'

curl -X GET localhost:1026/account/exy/resume

echo '\n'

curl -X GET localhost:1026/account/exy/groups

echo '\n'

curl -X GET localhost:1026/account/exy/resume/projects?token=123

echo '\n'

curl -X POST localhost:1026/account/exy/resume/projects?token=123

echo '\n'

curl -X DELETE localhost:1026/account/exy/resume/projects?token=123






