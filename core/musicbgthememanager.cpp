#include "musicbgthememanager.h"

MusicBgThemeManager::MusicBgThemeManager()
{
    m_currentIndex = 0;
}

void MusicBgThemeManager::clearArtName()
{
    m_currentArtName.clear();
}

void MusicBgThemeManager::setArtName(const QString &name)
{
    QString sName = name.split('-').front().trimmed();
    if(!m_currentArtName.isEmpty() && m_currentArtName != sName)
    {
        return;
    }

    m_photos.clear();
    QString filter = MusicObject::getAppDir() + ART_BG +
                     (m_currentArtName = sName) + "%1" + SKN_FILE;
    for(int i=0; i<MAX_INDEX; ++i)
    {
        if(QFile::exists(filter.arg(i)))
        {
            m_photos << filter.arg(i);
        }
    }
    emit artHasChanged();
}

QString MusicBgThemeManager::getArtPhotoPath()
{
    if(!m_photos.isEmpty())
    {
        return m_photos[m_currentIndex < m_photos.count() ?
                        m_currentIndex++ : m_currentIndex = 0];
    }
    else
    {
        return QString();
    }
}

QString MusicBgThemeManager::getArtPhotoPathByIndex(int index) const
{
    if((0 < index && index != -1) || index > m_photos.count() )
    {
        M_LOGGER << "index out of range" << LOG_END;
        return QString();
    }
    return (index == -1) ? m_photos[m_currentIndex < m_photos.count() ? m_currentIndex : 0]
                         : m_photos[index];
}

QStringList MusicBgThemeManager::getArtPhotoPaths() const
{
    return m_photos;
}

void MusicBgThemeManager::setArtPhotoPaths(const QStringList &list)
{
    m_photos = list;
}

void MusicBgThemeManager::sendUserSelectArtBg(int index)
{
    m_currentIndex = index;
}

void MusicBgThemeManager::setObject(QObject *obj) const
{
    connect(this,SIGNAL(artHasChanged()), obj, SLOT(artHasChanged()));
}
