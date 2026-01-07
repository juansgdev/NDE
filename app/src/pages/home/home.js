import { route } from "../../utils/routes.js"

const mapApps = (rawApps) => {
  return rawApps
    .split('\n')
    .map(line => line.trim())
    .filter(line => line)
    .map(line => {
      const [name, exec, icon] = line.split(',')

      return {
        name,
        exec,
        icon
      }
    })
}

export const loadPage = async () => {
    //app.innerHTML = await (await (await fetch(`./src/pages/${page}/${page}.html`)).text())
    const rawApps = await (await (await fetch('./src/data/apps.data')).text())
    const apps = mapApps(rawApps)

    const section = document.getElementsByTagName('section')[0]

    let index = 1
    apps.forEach(app => {
        const icon = document.createElement('div')
        icon.setAttribute('id', index)
        index++
        icon.innerHTML = `
            <img src="${app.icon}">
        `
        icon.onclick = () => {
            window.webkit.messageHandlers.app_entry.postMessage(`${app.exec} &`)
        }
        section.appendChild(icon)
    })

    index = 1
    document.getElementById(index).classList.add('selected')
    document.getElementById(index).scrollIntoView({
        behavior: 'smooth',
        block: 'center'
    })
    document.addEventListener('keydown', e => {
        e.preventDefault()
        if (e.key == 'ArrowLeft') {
            if (index == 1) index = apps.length
            else index--
        }
        if (e.key == 'ArrowRight') {
            if (index == apps.length) index = 1
            else index++
        }
        if (e.key == 'Enter') {
            document.getElementById(index).click()
        }

        document.querySelectorAll('.selected').forEach((app) => {
            app.classList.remove('selected')
        })
        
        document.getElementById(index).classList.add('selected')
        document.getElementById(index).scrollIntoView({
            behavior: 'smooth',
            block: 'center'
        })
    })

}

export const authAccess = () => {
    return true
}