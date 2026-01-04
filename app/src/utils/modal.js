export const modal = (content) => {
    document.body.style.pointerEvents = 'none'

    const modal = document.createElement('div')
    modal.id = 'modal'
    modal.classList.add('container')
    modal.classList.add('glass')
    modal.classList.add('aparecer')
    modal.innerHTML = content
    document.getElementsByTagName('body')[0].appendChild(modal)
    modal.style.pointerEvents = 'initial'
}

export const finishModal = () => {
    document.getElementById('modal').classList.replace('aparecer', 'desaparecer')
    
    setTimeout(() => {
        document.getElementById('modal').remove()
        document.body.style.pointerEvents = 'initial'
    }, 350)
}