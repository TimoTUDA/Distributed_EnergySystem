//
// Created by Philipp on 22.12.22.
//

#include "../../header/WebServer/HTMLGenerator.h"


HTMLGenerator::HTMLGenerator(){
    komponentenController = KomponentenController::getInstance();
};

HTMLGenerator::~HTMLGenerator() {

}

string HTMLGenerator::generateMainPage() {
    string s = generateHeader(false, "Zentrale");
    s += openBody(false);
    s += R"(<h5 class="headline">Energy Central</h5>)";
    s += generateMainTab();
    s += closeBody();
    std::replace(s.begin(), s.end(), '\n', ' ');

    return s;
}

string HTMLGenerator::generateSubPage(string& name, bool history) {
    Komponente* k = komponentenController->getKomponenteByName(name);

    //check if the requested component is part of the system
    if (k == nullptr)
        return "ALARM! Es gibt keine Komponente mit dem Namen \"" + name + "\".";

    string type = "Erzeuger";
    if (k->getType() == "Haushalt" || k->getType() == "Unternehmen");
        type = "Verbraucher";

    string s = generateHeader(false, name);
    s += openBody(false);

    s += "<h3>";
    s += "Overview for component " + name;
    s += "</h3>";

    s += R"(<button class="mdl-button mdl-js-button mdl-button--raised"
            onclick="window.location.href='/'">
                Back to Menu
            </button>)";

    string t = k->getType();

    if (history){
        s += generateTableHead(type);
        std::map<time_t , double> map = k->getValues();
        for (auto it = map.begin(); it != map.end(); ++it){
            s += generateTableRow(t, name, k->getId(), it->second, it->first);
        }
        s += closeTable();
    }
    s += closeBody();
    std::replace(s.begin(), s.end(), '\n', ' ');

    return s;
}

string HTMLGenerator::generateHeader(bool mainPage, string title) {
    string header = R"(<!DOCTYPE html>
<html lang="en">
<head>
    <link rel="stylesheet" href="https://fonts.googleapis.com/icon?family=Material+Icons">
    <link rel="stylesheet" href="https://code.getmdl.io/1.3.0/material.indigo-pink.min.css">
    <link rel="stylesheet" href="http://fonts.googleapis.com/css?family=Roboto:300,400,500,700" type="text/css">
    <script defer src="https://code.getmdl.io/1.3.0/material.min.js"></script>
    <script type="text/javascript">
        function changeStatus(id) {
        console.log(id);

        let button = document.getElementById(id);
        console.log(button.getAttribute("class"));
         if (button.getAttribute("class") == "mdl-button mdl-js-button mdl-button--raised mdl-js-ripple-effect mdl-button--accent") {
            console.log("if");
            button.setAttribute("class", "mdl-button mdl-js-button mdl-button--raised mdl-js-ripple-effect mdl-button--colored");
        } else {
            console.log("else");
            button.setAttribute("class", "mdl-button mdl-js-button mdl-button--raised mdl-js-ripple-effect mdl-button--accent");
        }


        let req = new XMLHttpRequest();
        let url = "/SetStatus?id=";
        url += id;
        req.open("GET", url);
        req.send();
        }
    </script>
    <meta charset="UTF-8">
    <title>)";
    header += title;
    header += R"(</title> </head>)";

    if (mainPage)
        header += R"(
        <script>
        function openMainTab(evt, type) {

        var i, tabcontent, tablinks;


        tabcontent = document.getElementsByClassName('mdl-tabs mdl-js-tabs mdl-js-ripple-effect');
        for (i = 0; i < tabcontent.length; i++) {
            tabcontent[i].style.display = 'none';
        }


        tablinks = document.getElementsByClassName('mdl-button mdl-js-button mdl-js-ripple-effect');
        for (i = 0; i < tablinks.length; i++) {
            tablinks[i].className = tablinks[i].className.replace(' active', '');
        }

        document.getElementById(type).style.display = 'block';
        evt.currentTarget.className += ' active';
        }
        </script>)";
    return header;
}

string HTMLGenerator::generateMainTab() {
    string s = R"(    <div class="mdl-tabs mdl-js-tabs mdl-js-ripple-effect">
  <div class="mdl-tabs__tab-bar">
      <a href="#erzeugerPanel" class="mdl-tabs__tab is-active">Producer</a>
      <a href="#verbraucherPanel" class="mdl-tabs__tab">Consumer</a>
  </div>)";
    s += R"(<div class="mdl-tabs__panel is-active" id="erzeugerPanel">)";
    s += generateSubTabs("Erzeuger");
    s += "</div>";
    s += R"(<div class="mdl-tabs__panel" id="verbraucherPanel">)";
    s += generateSubTabs("Verbraucher");
    s += "</div>";
    s += "</div>";
    return s;
}

string HTMLGenerator::generateSubTabs(string type) {
    string s = generateKomptTableHead(type);
    std::vector<Komponente*> list;
    if (type == "Erzeuger")
        list = komponentenController->getErzeuger();
    else
        list = komponentenController->getVerbraucher();

    for (int i = 0; i < list.size(); ++i){
        string t = list[i]->getType();
        string name = list[i]->getName();
        int id = list[i]->getId();
        bool status = false;
        Erzeuger* erzeuger = dynamic_cast<Erzeuger*> (list[i]);
        if (erzeuger != nullptr) {
            status = erzeuger->isStatus();
        }

        s+= generateKompTableRow(type, name, id, status);
    }
    s += closeTable();
    return s;
}

string HTMLGenerator::openBody(bool mainPage) {
    if (mainPage)
        return R"(<body onload="openMainTab(event, 'Erzeuger') ">)";
    else
        return R"(<body>)";
}

string HTMLGenerator::closeBody() {
    string body = R"(</body> </html>)";
    return body;
}

string HTMLGenerator::generateTableHead(string& type) {
    string headerText = "";
    if (type == "Erzeuger")
        headerText = "Voltage input";
    else
        headerText = "Energy consumption";

    string s = R"(<table class="mdl-data-table mdl-js-data-table mdl-data-table--selectable mdl-shadow--2dp">)";
    s += "<tr>";
    s += R"(<th>)";
    s += "Type";
    s += R"(</th>)";
    s += R"(<th>)";
    s += "Name";
    s += R"(</th>)";
    s += R"(<th>)";
    s += "ID";
    s += R"(</th>)";
    s += R"(<th>)";
    s += headerText;
    s += R"(</th>)";
    s += R"(<th>)";
    s += "Time";
    s += R"(</th>)";
    s += R"(</tr>)";
    return s;
}

string HTMLGenerator::generateTableRow(string& type, string name, int id, double value, time_t time) {
    string s;

    s += "<tr>";
    s += "<td>";
    s += type;
    s += R"(</td>)";
    s += "<td>";
    s += name;
    s += R"(</td>)";
    s += "<td>";
    s += to_string(id);
    s += R"(</td>)";
    s += "<td>";
    s += to_string(value);
    s += R"(</td>)";
    s += "<td>";
    char* timeString  = ctime(&time);
    s += timeString;
    s += R"(</td>)";
    s += R"(</tr>)";
    return s;
}

string HTMLGenerator::closeTable() {
    return "</table>";
}

string HTMLGenerator::generateKomponentenListe(string type) {
    return std::string();
}

string HTMLGenerator::generateKomptTableHead(string type) {
    string s = R"(<table class="mdl-data-table mdl-js-data-table mdl-data-table--selectable mdl-shadow--2dp">)";
    s += "<tr>";
    s += R"(<th>)";
    s += "Typ";
    s += R"(</th>)";
    s += R"(<th>)";
    s += "Name";
    s += R"(</th>)";
    s += R"(<th>)";
    s += "ID";
    s += R"(</th>)";
    s += R"(<th>)";
    s += "Details";
    s += R"(</th>)";

    //button hinzufügen
    if (type == "Erzeuger") {
        s += R"(<th>)";
        s += "Turn on/off";
        s += R"(</th>)";
    }

    s += R"(</tr>)";
    return s;
}

string HTMLGenerator::generateKompTableRow(string& type, string name, int id, bool status) {
    string s;

    s += "<tr>";
    s += "<td>";
    s += type;
    s += R"(</td>)";
    s += "<td>";
    s += name;
    s += R"(</td>)";
    s += "<td>";
    s += to_string(id);
    s += R"(</td>)";
    s += "<td>";
    s += R"(<a href="/Detail?name=)" + name + R"(&history=true">Details</a>)";
    s += R"(</td>)";

    if (type == "Erzeuger") {
        s += R"(<td>)";
        s += R"(<button id=")";
        s += to_string(id);
        if (!status) {
            s += R"(" type="button"
            class="mdl-button mdl-js-button mdl-button--raised mdl-js-ripple-effect mdl-button--accent"
            onclick="changeStatus(this.id)";
        } else {
            s += R"(" type="button"
            class="mdl-button mdl-js-button mdl-button--raised mdl-js-ripple-effect mdl-button--colored"
            onclick="changeStatus(this.id)";
        }
        s += ")";
        s += R"(">change status </button>)";
        s += R"(</td>)";
    }

    s += R"(</tr>)";
    return s;
}

string HTMLGenerator::handleStatusChange(int id) {
    string retMsg = "Status der Komponente erfolgreich geändert";
    try {
        Komponente* komp = komponentenController->getKomponenteById(id);
        if (komp == nullptr)
            throw invalid_argument("Es ist keine Komponente mit der ID " + to_string(id) + "vorhanden");
        ErzeugerRpcClient* rpcClient = new ErzeugerRpcClient();
        rpcClient->initRpc(komp->getIp(), 7000);
        rpcClient->changeStatus(id);
        delete rpcClient;
    } catch (exception &e) {
        cerr << e.what() << endl;
        retMsg = e.what();
    }
    return retMsg;
}
