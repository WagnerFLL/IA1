knowledge = {}
rule = {}


def build_knowledge(data, value):
    if data[0] == '!':
        knowledge[data[1:]] = not value
        knowledge[data] = value
    else:
        knowledge[data] = value
        knowledge['!' + data] = not value


def build_rules(data):
    data = data.replace('^', ' ').split('=')

    handle = [x for x in data[0].split(' ') if x != '']
    head = data[1].replace(' ', '').split(',')

    for x in head:
        if x not in rule:
            rule[x] = []
        rule[x].append(handle)


def test_reverse(quest):
    if quest[0] == '!':
        if quest not in rule:
            return True, quest[1:]
        return False, quest

    else:
        if quest not in rule:
            return True, '!' + quest
        return False, quest


def backward(quest):
    reverse, quest = test_reverse(quest)

    if quest in knowledge:
        return knowledge[quest]

    for x in rule[quest]:
        result = True

        for i in x:
            if i not in knowledge:
                answer = backward(i)
                build_knowledge(i, answer)
            result = result and knowledge[i]

        if reverse:
            return not result
        return result


def forward():
    elements = []

    for x in rule.keys():
        elements.append(x)

    while elements:
        x = elements.pop(0)
        for i in rule[x]:
            result = True
            for k in i:
                if k not in knowledge:
                    break
                result = result and knowledge[k]
            else:
                build_knowledge(x, result)
                break
            elements.append(x)


print("Base de conhecimento: ")
print("Ex.: 'A' ou '!A' ")
enter = input()
while enter != '':
    build_knowledge(enter, True)
    enter = input()

print("Base de regras")
print("Ex.: A ^ B ^ !C = D,E ")
enter = input()
while enter != '':
    build_rules(enter)
    enter = input()

print("Escolha o modo de operação:\n " +
      "1 - Encadeamento para frente.\n" +
      "2 - Encadeamento para trás. ")
choice = int(input())

print("Pergunte:")
print("Ex.: 'A', 'B'")
enter = input()
while enter != '':

    if enter in knowledge:
        print(knowledge[enter])
    else:
        if choice == 1:
            forward()
            print(knowledge[enter])
        else:
            print(backward(enter))

    enter = input()
