#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

struct Quest {
    string name;
    string type;
    int xpReward;
    bool completed;
};

struct Reward {
    string name;
    int cost;
};

class Player {
public:
    string name;
    int hp;
    int maxHp;
    int xp;
    vector<Quest> quests;
    vector<Reward> rewards;

    Player() : hp(100), maxHp(100), xp(0) {
        rewards.push_back({"10-min break", 50});
        rewards.push_back({"30-min nap", 120});
        rewards.push_back({"20-min Netflix", 150});
        rewards.push_back({"1-hour gaming", 300});
        rewards.push_back({"Cheat meal", 200});
    }

    void earnXP(int amount) {
        xp += amount;
    }
};

string readLine(const string& prompt) {
    cout << prompt;
    string s;
    getline(cin, s);
    return s;
}

int readInt(const string& prompt) {
    int n;
    while (true) {
        cout << prompt;
        if (cin >> n) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return n;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Please enter a valid number.\n";
    }
}

void printHPBar(Player& p) {
    int filled = (p.hp * 20) / p.maxHp;
    int empty  = 20 - filled;
    cout << "  HP  [" << string(filled, '#') << string(empty, '.') << "]  "
         << p.hp << "/" << p.maxHp << "\n";
}

void printHeader(Player& p) {
    cout << "\n================================\n";
    cout << "   QUEST LOG  -  Task Manager  \n";
    cout << "================================\n";
    cout << "  Player : " << p.name << "\n";
    printHPBar(p);
    cout << "  XP     : " << p.xp << " pts\n";
    cout << "--------------------------------\n";
}

void viewQuests(Player& p) {
    cout << "\n--- YOUR QUESTS ---\n";
    if (p.quests.empty()) {
        cout << "  No quests yet.\n";
        return;
    }
    for (int i = 0; i < p.quests.size(); i++) {
        Quest& q = p.quests[i];
        cout << i + 1 << ". "
             << (q.completed ? "[DONE] " : "[ACTIVE] ")
             << q.name << " [" << q.type << "] +"
             << q.xpReward << " XP\n";
    }
}

void addQuest(Player& p) {
    Quest q;
    q.completed = false;

    q.name = readLine("Quest name: ");

    cout << "Type: 1=Daily 2=Weekly 3=Monthly\n";
    int t = readInt("Choice: ");
    q.type = (t == 1) ? "Daily" : (t == 2) ? "Weekly" : "Monthly";

    q.xpReward = readInt("XP: ");
    p.quests.push_back(q);

    cout << "Quest added!\n";
}

void completeQuest(Player& p) {
    viewQuests(p);
    if (p.quests.empty()) return;

    int idx = readInt("Quest number: ") - 1;
    if (idx < 0 || idx >= p.quests.size()) return;

    if (!p.quests[idx].completed) {
        p.quests[idx].completed = true;
        p.earnXP(p.quests[idx].xpReward);
        cout << "Completed! +" << p.quests[idx].xpReward << " XP\n";
    }
}

void deleteQuest(Player& p) {
    viewQuests(p);
    if (p.quests.empty()) return;

    int idx = readInt("Delete number: ") - 1;
    if (idx >= 0 && idx < p.quests.size())
        p.quests.erase(p.quests.begin() + idx);
}

void rewardShop(Player& p) {
    cout << "\nXP: " << p.xp << "\n";
    for (int i = 0; i < p.rewards.size(); i++) {
        cout << i + 1 << ". " << p.rewards[i].name
             << " (" << p.rewards[i].cost << ")\n";
    }

    int idx = readInt("Choose reward: ") - 1;
    if (idx >= 0 && idx < p.rewards.size()) {
        if (p.xp >= p.rewards[idx].cost) {
            p.xp -= p.rewards[idx].cost;
            cout << "Unlocked!\n";
        }
    }
}

int main() {
    Player p;

    cout << "Enter your name: ";
    getline(cin, p.name);

    while (true) {
        printHeader(p);

        cout << "\n1.View 2.Add 3.Complete 4.Delete 5.Shop 7.Quit\n";
        int c = readInt("Choice: ");

        switch (c) {
            case 1: viewQuests(p); break;
            case 2: addQuest(p); break;
            case 3: completeQuest(p); break;
            case 4: deleteQuest(p); break;
            case 5: rewardShop(p); break;
            case 7: return 0;
        }
    }
}