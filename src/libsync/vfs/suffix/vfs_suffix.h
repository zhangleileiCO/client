/*
 * Copyright (C) by Christian Kamm <mail@ckamm.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 */
#pragma once

#include <QObject>
#include <QScopedPointer>

#include "common/vfs.h"
#include "common/plugin.h"

namespace OCC {

class VfsSuffix : public VfsDefaults
{
    Q_OBJECT

public:
    explicit VfsSuffix(QObject *parent = nullptr);
    ~VfsSuffix();

    Mode mode() const override;
    QString fileSuffix() const override;

    void stop() override;
    void unregisterFolder() override;

    bool socketApiPinStateActionsShown() const override { return true; }
    bool isHydrating() const override;

    bool updateMetadata(const QString &filePath, time_t modtime, quint64 size, const QByteArray &fileId, QString *error) override;

    void createPlaceholder(const SyncFileItem &item) override;
    void dehydratePlaceholder(const SyncFileItem &item) override;
    void convertToPlaceholder(const QString &filename, const SyncFileItem &item, const QString &) override;

    bool isDehydratedPlaceholder(const QString &filePath) override;
    bool statTypeVirtualFile(csync_file_stat_t *stat, void *stat_data) override;

public slots:
    void fileStatusChanged(const QString &, SyncFileStatus) override {}
};

class SuffixVfsPluginFactory : public QObject, public DefaultPluginFactory<VfsSuffix>
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.owncloud.PluginFactory" FILE "vfspluginmetadata.json")
    Q_INTERFACES(OCC::PluginFactory)
};

} // namespace OCC
