export default (duration: number) => {
    return (Math.round((duration / 1000) * 100) / 100) + " s"
}