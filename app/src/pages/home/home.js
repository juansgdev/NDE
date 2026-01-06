import { route } from "../../utils/routes.js"

export const loadPage = async () => {
    //app.innerHTML = await (await (await fetch(`./src/pages/${page}/${page}.html`)).text())
    const apps = await (await (await fetch('./src/data/apps.data')).text())

    document.getElementsByTagName('p')[0].innerHTML = apps

    document.getElementsByTagName('button')[0].onclick = () => {
        window.webkit.messageHandlers.app_entry.postMessage("pcmanfm &");
    }
}

export const authAccess = () => {
    return true
}